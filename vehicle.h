#include "graphics.h"
#pragma once
const float YCar = 250.f;
const float YTruck = 750.f;


class CVEHICLE {
private:
	int mX, mY;

public:
	void Move(float x, float y);
	void setPosition(float x, float y);
	void drawInWindow(sf::RenderWindow& window);
	virtual void loadTexture(float x) = 0;
	virtual sf::Sprite getSprite() = 0;
	virtual sf::Texture getTexture() = 0;
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	//lam thu virtual get set voi 2 cai texture/sprite
};

class CCAR : public CVEHICLE {
public:
	//CCAR(); //load sprite tu texture o day
	/*CCAR(float x);*/
	void loadTexture(float x);
	sf::Sprite getSprite();
	sf::Texture getTexture();
};


class CTRUCK : public CVEHICLE {
public:
	//CTRUCK();
	/*CTRUCK(float x);*/
	void loadTexture(float x);
	sf::Sprite getSprite();
	sf::Texture getTexture();
};

extern std::vector<CCAR> cars;
extern std::vector<CCAR> generatedCars;
void generateCar(); //tao mot xe

void drawCar(sf::RenderWindow& window, std::vector<CCAR>& generatedCars);