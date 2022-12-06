#pragma once

#include<SFML/Graphics.hpp>

class CANIMAL {
	int mX, mY;
public:
	virtual void Move(float, float);
	virtual void Tell();

	virtual sf::Texture getTexture();
	virtual sf::Sprite getSprite();

	virtual void setPosition(float x, float y);

	virtual void drawInWindow(sf::RenderWindow& window);
};

class CDINAUSOR : public CANIMAL {
public:
	//...
};

class CBIRD : public CANIMAL {
public:
	//...
};