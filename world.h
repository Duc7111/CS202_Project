#pragma once
#include <cmath>
#include <deque>
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
	void forward();
	bool backward();
	void drawWorld(sf::RenderWindow& window);
	void checkCollide(sf::RenderWindow& window, CPEOPLE player);
	std::deque<Road*> object;
	int getForwardIndex() const;
	friend std::ofstream& operator<<(std::ofstream& ofs, const WORLD& world);
	friend void inputRoads(std::ifstream& ifs, sf::RenderWindow& window, WORLD& world);
private:
	static float calculateVelocity(int index);
	Road* createRoad(int index);
	SEED seed;
	int forwardIndex;
	int backwardIndex;
};

class BACKGROUND {
public:
	BACKGROUND();
	void update(const WORLD& world);
	void updateOnLoad(const WORLD& world); // act like a hotfix
	void draw(sf::RenderWindow& window);
private:
	sf::Texture texture;
	std::deque<sf::Sprite> sprite;
};