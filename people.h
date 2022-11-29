#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "animal.h"
#include "vehicle.h"

class CPEOPLE {
	int mX, mY; // position in the cell-based location system
	bool mState; // state of living (mState = true if player is alive)

	sf::Texture texture[4];
	static sf::Vector2f drawPosition(int mX, int mY);
public:
	unsigned int mDirection; // current direction of moving (default = 0, up = 1, down = 2, right = 3, left = 4)
	sf::Sprite sprite;
	CPEOPLE();
	void loadTexture(); // load texture
	void drawInWindow(sf::RenderWindow& window); // draw current object	sf::Vector2i getPosition(); // Return mY, mX in the form of sf::Vector2i
	sf::Vector2i getPosition() const;
	void goUp(); // go up
	void goDown(); // go down
	void goRight(); // go right
	void goLeft(); // go left
	bool isImpact(const CVEHICLE*&);
	bool isImpact(const CANIMAL*&);
	bool isFinish();
	bool isDead();
};
