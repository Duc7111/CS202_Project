#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

#include "collider.h"

class CVEHICLE;
class CANIMAL;

class CPEOPLE {
	int mX, mY; // position in the cell-based location system
	int mPrevY = 0; //y truoc do
	bool mState; // state of living (mState = true if player is alive)
	sf::Texture texture[4];
	static sf::Vector2f drawPosition(int mX, int mY);
	sf::Sprite sprite;
	unsigned int mDirection; // current direction of moving (default = 0, up = 1, down = 2, right = 3, left = 4)
	sf::Image img;


public:
	CPEOPLE();
	void loadTexture(); // load texture
	void drawPlayer(sf::RenderWindow& window); // draw current object	sf::Vector2i getPosition(); // Return mY, mX in the form of sf::Vector2i
	sf::Vector2i getPosition() const;
	int getPrevY() const;
	sf::Vector2f getPositionInWorld() const;
	unsigned int getDirection() const;
	void goUp(); // go up
	void goDown(); // go down
	void goRight(); // go right
	void goLeft(); // go left
	bool isImpact(const CVEHICLE*&);
	bool isImpact(const CANIMAL*&);
	bool isFinish();
	bool isDead();

	sf::Sprite getSprite() { return sprite; }
	sf::Texture getTexture() { return texture[0]; }


	bool reinitializedVehicle = false;

	bool collidedWithEnemy();

};
