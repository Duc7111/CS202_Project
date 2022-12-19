#include "world.h"
#include "game.h"

WORLD::WORLD() {
	//std::fill(object, object + 9, nullptr);
	forwardIndex = 6;
	backwardIndex = 0;
}

WORLD::~WORLD() {
	while (!object.empty()) {
		Road* tmp = object.front();
		object.pop_front();
		delete tmp;
	}
}

void WORLD::createWorld(sf::RenderWindow& window) {
	Road::setWindow(&window);
	object.push_front(nullptr);
	object.push_front(nullptr);
	for (int i = 0; i < 7; ++i) {
		Road* tmp = createRoad(i);
		object.push_back(tmp);
	}
	window.draw(CGAME::currentScore);
}

void WORLD::loadBackground() {
	texture.loadFromFile("bg.png");
	sprite.setTexture(texture);
}

void WORLD::forward() {
	if (backwardIndex < 0) {
		++backwardIndex;
		return;
	}
	++forwardIndex;
	Road* tmp = object.front();
	object.pop_front();
	delete tmp;
	if (forwardIndex % 7 == 0) seed.update();
	tmp = createRoad(forwardIndex);
	object.push_back(tmp);
}

bool WORLD::backward() {
	if (backwardIndex == -2) return false;
	--backwardIndex;
	return true;
}

void WORLD::drawWorld(sf::RenderWindow& window) {
	for (int i = 0; i < 7; ++i) {
		if (object[i]) {
			//object[i]->setPosition(forwardIndex + i - 2);
			object[i]->drawRoad();
		}
	}
	for (int i = 6; i >= 0; --i) {
		if (object[i]) {
			object[i]->setVelocity(7.f);
			object[i]->run();
			object[i]->drawObj();
		}
	}
	window.draw(CGAME::currentScore);
}

Road* WORLD::createRoad(int index) {
	Road* tmp = nullptr;
	switch (seed[index]) {
	case base:
		return nullptr;
	case vehicle:
		tmp = new VehicleRoad;
		tmp->resetSprite();
		tmp->setPosition(index);
		return tmp;
	case animal:
		tmp = new AnimalRoad;
		tmp->resetSprite();
		tmp->setPosition(index);
		return tmp;
	default:
		break;
	}
	return nullptr;
}

void WORLD::checkCollide(sf::RenderWindow& window, CPEOPLE player) {
	for (int i = 0; i < object.size(); i++)
		if (object[i])
			if (IsNearby(player, object[i]->sprite, 5))
				if (object[i] && object[i]->checkCollide(window, player))
					return;
}
