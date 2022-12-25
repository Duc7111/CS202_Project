#pragma once

#include<SFML/Graphics.hpp>
#include "people.h"
#include <SFML/Audio.hpp>

class CANIMAL {

protected:
	int mX, mY;
	float speed;
	sf::Sprite sprite;

	sf::Vector2f currentPos;
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

	sf::Vector2f getCurrentPos();
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
	bool isSetSound = false;
	sf::SoundBuffer tellBuffer;
	sf::Sound tell;
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
	bool isSetSound = false;
	sf::SoundBuffer tellBuffer;
	sf::Sound tell;
};
