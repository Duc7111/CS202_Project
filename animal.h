#pragma once

#include<SFML/Graphics.hpp>

class CANIMAL {



protected:
	int mX, mY;
	float speed;
	sf::Sprite sprite;
public:
	void Move(float, float);
	virtual void Tell() = 0;

	virtual sf::Texture getTexture() = 0;
	virtual sf::Sprite getSprite() = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual void setSpeed(float speed) = 0;

	void setPosition(float x, float y);

	virtual void drawInWindow(sf::RenderWindow& window) = 0;

	friend void scale(CANIMAL*, float, float);
};

class CDINAUSOR : public CANIMAL {
public:
	CDINAUSOR();
	void Tell();
	sf::Vector2f getPosition();

	sf::Texture getTexture();
	sf::Sprite getSprite();

	void setSpeed(float speed);
	void drawInWindow(sf::RenderWindow& window);

};

class CBIRD : public CANIMAL {
public:
	CBIRD();
	void Tell();
	sf::Vector2f getPosition();
	sf::Texture getTexture();
	sf::Sprite getSprite();

	void drawInWindow(sf::RenderWindow& window);
	void setSpeed(float speed);
};
