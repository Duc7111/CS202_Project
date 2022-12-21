#pragma once

#include<SFML/Graphics.hpp>
#include "people.h"

class CANIMAL {

protected:
	int mX, mY;
	float speed;
	sf::Sprite sprite;
public:
	void Move(float x, float y);
	virtual void Tell() = 0;

	virtual sf::Texture getTexture() = 0;
	sf::Sprite getSprite();
	virtual sf::Vector2f getPosition() = 0;
	virtual void setSpeed(float speed) = 0;

	void setPosition(float x, float y);

	virtual void drawInWindow(sf::RenderWindow& window) = 0;

	friend void scale(CANIMAL*, float, float);

	virtual bool CollidedWithPlayer(CPEOPLE player) = 0;

	bool isElephant;
};

class CELEPHANT : public CANIMAL {
public:
	CELEPHANT();
	void Tell();
	sf::Vector2f getPosition();

	sf::Texture getTexture();
	sf::Sprite getSprite();

	void setSpeed(float speed);
	void drawInWindow(sf::RenderWindow& window);
	bool CollidedWithPlayer(CPEOPLE player);
};

class CCAT : public CANIMAL {
public:
	CCAT();
	void Tell();
	sf::Vector2f getPosition();
	sf::Texture getTexture();
	sf::Sprite getSprite();

	void drawInWindow(sf::RenderWindow& window);
	void setSpeed(float speed);
	bool CollidedWithPlayer(CPEOPLE player);
};
