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
			object[i]->drawRoad();
			object[i]->run();
			object[i]->drawObj();
		}
		else {
			drawTrees(window, treeIndex + i);
		}

	}
	treeIndex += 6;
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
		tmp->setVelocity(calculateVelocity(index));
		return tmp;
	case animal:
		tmp = new AnimalRoad;
		tmp->resetSprite();
		tmp->setPosition(index);
		tmp->setVelocity(calculateVelocity(index));
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

int WORLD::getForwardIndex() const {
	return forwardIndex;
}

float WORLD::calculateVelocity(int index) {
	static vector<float> v = { 0.f, 0.0 };
	if (v.size() <= index)
		for (int i = v.size() - 1; i <= index; ++i)
			v.push_back(511.f / 512.f * v[i] + 0.03125f);
	return v[index];
	//return ((index - static_cast<float>(6)) / (13)) + sin(((index - static_cast<float>(6)) / (13)));
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

		temp->setWindow(&window);
		temp->resetSprite();

		temp->input(ifs);

		temp->setPosition(index);

		world.object.push_back(temp);
	}
}

BACKGROUND::BACKGROUND() {
	texture.loadFromFile("TX Tileset Grass.png", sf::IntRect(0, 0, 128, 128));
	texture.setRepeated(true);
	for (int i = 0; i < 2; ++i) {
		sprite.push_back(sf::Sprite());
		sprite.back().setTexture(texture);
		sprite.back().setTextureRect(sf::IntRect(0, 0, 1536, 1536));
		sprite.back().setPosition(0, i * -1300);
	}
}

void BACKGROUND::update(const WORLD& world) {
	int index = world.getForwardIndex();
	if (index % 15 == 0) {
		sf::Sprite tmp = sprite.front();
		sprite.pop_front();
		tmp.setPosition(0, (index / 15 + 1) * -1300);
		sprite.push_back(tmp);
	}
}

void BACKGROUND::updateOnLoad(const WORLD& world) {
	int index = world.getForwardIndex();
	for (int i = 0; i < 2; ++i) {
		sprite[i].setPosition(0, (index / 15 + i) * -1300);
	}
}

void BACKGROUND::draw(sf::RenderWindow& window) {
	for (auto& bg : sprite) {
		window.draw(bg);
	}
}
