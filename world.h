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
	void checkCollide(sf::RenderWindow& window, CPEOPLE player);
	std::deque<Road*> object;
private:
	Road* createRoad(int index);
	sf::Texture texture;
	sf::Sprite sprite;
	SEED seed;

	int forwardIndex;
	int backwardIndex;
};