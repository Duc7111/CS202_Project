#pragma once
#include <deque>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "seed.h"
#include "people.h"
#include "road.h"

class TERRAIN {

};

class WORLD {
public:
	WORLD();
	~WORLD();
	void createWorld(sf::RenderWindow& window);
	void loadBackground();
	void forward();
	bool backward();
	void drawWorld(sf::RenderWindow& window);
private:
	Road* createRoad(int index);
	sf::Texture texture;
	sf::Sprite sprite;
	SEED seed;
	std::deque<Road*> object;
	int forwardIndex;
	int backwardIndex;
};