#include "graphics.h"
#pragma once
extern float YCar;
extern float YTruck;

class CVEHICLE {
private:
	int mX, mY;

public:
	void Move(float x, float y);
	void setPosition(float x, float y);
	void drawInWindow(sf::RenderWindow& window);
	virtual void loadTexture(float x) = 0;
	virtual void loadTextureForeground(float x) = 0; //tao sprite cho background phu
	virtual sf::Sprite getSprite() = 0;
	//virtual sf::Texture getTexture() = 0;
protected:
	sf::Sprite sprite;
	//sf::Texture texture;
	//lam thu virtual get set voi 2 cai texture/sprite
};

class CCAR : public CVEHICLE {
private:

public:
	CCAR(); //load sprite tu texture o day
	/*CCAR(float x);*/
	void loadTexture(float x);
	sf::Sprite getSprite();
	//sf::Texture getTexture();

	void loadTextureForeground(float x);
};


class CTRUCK : public CVEHICLE {
private:
	static sf::Texture truckTextre;
public:
	CTRUCK();
	/*CTRUCK(float x);*/
	void loadTexture(float x);
	sf::Sprite getSprite();

	void loadTextureForeground(float x);
	//sf::Texture getTexture();
};


void generateCar(); //tao mot xe

