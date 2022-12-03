#pragma once

#include<SFML/Graphics.hpp>

class CANIMAL {
	int mX, mY;
public:
	virtual void Move(int, int);
	virtual void Tell();
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