#pragma once

#include<SFML/Graphics.hpp>

class CANIMAL {
	int mX, mY;
protected:
	sf::Sprite sprite;
public:
	void Move(float, float);
	virtual void Tell() = 0;

	virtual sf::Texture getTexture() = 0;
	virtual sf::Sprite getSprite() = 0;

	void setPosition(float x, float y);

	virtual void drawInWindow(sf::RenderWindow& window) = 0;

	friend void scale(CANIMAL*, float, float);
};

class CDINAUSOR : public CANIMAL {
public:
	void Tell();

	sf::Texture getTexture();
	sf::Sprite getSprite();

	void drawInWindow(sf::RenderWindow& window);
};

class CBIRD : public CANIMAL {
public:
	void Tell();

	sf::Texture getTexture();
	sf::Sprite getSprite();

	void drawInWindow(sf::RenderWindow& window);
};