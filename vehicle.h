#include "graphics.h"
#pragma once
const float YCar = 250.f;
const float YTruck = 500.f;


class CVEHICLE {
private:
	int mX, mY;
public:
	void Move(float x, float y);
	sf::Sprite sprite;
protected:
	sf::Texture texture;
};

class CCAR : public CVEHICLE {
public:
	CCAR(); //load sprite tu texture o day
	CCAR(float x);
	void setPosition(float x, float y);
};


class CTRUCK : public CVEHICLE {
public:
	CTRUCK();
	CTRUCK(float x);

};

extern std::vector<CCAR> cars;
extern std::vector<CCAR> generatedCars;
void generateCar(); //tao mot xe

void drawCar(sf::RenderWindow& window, std::vector<CCAR>& generatedCars);