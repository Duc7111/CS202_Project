#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "seed.h"
#include "people.h"
#include "road.h"

class WORLD {
public:
	WORLD();
	~WORLD();
	void createWorld(sf::RenderWindow& window);
	void loadBackground();
	void forward();
	void backward(CPEOPLE& player);
	void drawWorld(sf::RenderWindow& window);
private:
	static Road* createRoad(SEED_T seed_type);
	sf::Texture texture;
	sf::Sprite sprite;
	SEED seed;
	Road* object[9];
	int forwardIndex;
};