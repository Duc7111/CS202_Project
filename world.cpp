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

std::ofstream& operator<<(std::ofstream& ofs, const WORLD& world) {
	ofs.write((char*)&world.forwardIndex, sizeof(world.forwardIndex));
	ofs.write((char*)&world.backwardIndex, sizeof(world.backwardIndex));

	for (int i = 0; i < world.object.size(); i++) {
		bool isRoad = world.object[i];
		ofs.write((char*)&isRoad, sizeof(isRoad));
		if (!isRoad)
			continue;
		bool isVehicleRoad = world.object[i]->isVehicleRoad;
		ofs.write((char*)&isVehicleRoad, sizeof(isVehicleRoad));
		ofs.write((char*)&world.object[i]->index, sizeof(world.object[i]->index));
		world.object[i]->output(ofs);
	}

	return ofs;
}

void inputRoads(std::ifstream& ifs, sf::RenderWindow& window, WORLD& world) {
	ifs.read((char*)&world.forwardIndex, sizeof(int));
	ifs.read((char*)&world.backwardIndex, sizeof(int));

	for (int i = 0; i < 7; i++) {
		bool isRoad;
		ifs.read((char*)&isRoad, sizeof(bool));
		if (!isRoad)
		{
			world.object.push_back(nullptr);
			continue;
		}
		Road* temp;
		bool isVehicleRoad;
		ifs.read((char*)&isVehicleRoad, sizeof(bool));
		if (isVehicleRoad) {
			temp = new VehicleRoad;
		}
		else {
			temp = new AnimalRoad;
		}
		temp->isVehicleRoad = isVehicleRoad;
		int index;
		ifs.read((char*)&index, sizeof(int));
		temp->index = index;
		temp->input(ifs);
		temp->setWindow(&window);
		temp->resetSprite();
		temp->setPosition(index);
		world.object.push_back(temp);
	}
}