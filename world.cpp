#include "world.h"
#include "game.h"

WORLD::WORLD() {
	std::fill(object, object + 9, nullptr);
	forwardIndex = 0;
}

WORLD::~WORLD() {
	for (int i = 0; i < 9; ++i) {
		delete object[i];
	}
}

void WORLD::createWorld(sf::RenderWindow& window) {

	Road::setWindow(&window);
	for (int i = 0; i < 7; ++i) {
		object[i + 2] = createRoad(seed[i]);
	}
	window.draw(CGAME::currentScore);
}

void WORLD::loadBackground() {
	texture.loadFromFile("bg.png");
	sprite.setTexture(texture);
}

void WORLD::forward() {
	++forwardIndex;
	delete object[0];
	for (int i = 0; i < 8; ++i) {
		object[i] = object[i + 1];
	}
	if (forwardIndex % 7 == 0) seed.update();
	object[8] = createRoad(seed[forwardIndex]);
}

void WORLD::backward(CPEOPLE& player) {

}

void WORLD::drawWorld(sf::RenderWindow& window) {

	for (int i = 0; i < 7; ++i) {
		if (object[i]) {
			object[i]->setPosition(forwardIndex + i - 2);
			object[i]->setVelocity(10.f);
			object[i]->run();
			object[i]->draw();
		}
	}
	window.draw(CGAME::currentScore);
}

Road* WORLD::createRoad(SEED_T seed_type) {
	Road* tmp = nullptr;
	switch (seed_type) {
	case base:
		return nullptr;
	case vehicle:
		tmp = new VehicleRoad;
		tmp->resetSprite();
		return tmp;
	case animal:
		tmp = new VehicleRoad;
		tmp->resetSprite();
		return tmp;
	default:
		break;
	}
	return nullptr;
}
