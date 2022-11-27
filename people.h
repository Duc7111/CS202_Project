#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

class CPEOPLE {
	int mX, mY;
	bool mState; // state of living (mState = true if player is alive)
	int mDirection; // current direction of moving 
	sf::Texture texture[4];
	sf::Sprite sprite;
public:
	void loadTexture(); // load texture
	void drawInWindow(sf::RenderWindow& window); // draw current object
	sf::Vector2i getPosition(); // Return mY, mX in the form of sf::Vector2i
	void goUp();
	void goDown();
	void goLeft();
	void goRight();
	//bool isImpact(const CVEHICLE*&);
	//bool isImpact(const CANIMAL*&);
	//bool isFinish();
	//bool isDead();
};
