#include "graphics.h"
#pragma once
const float Y = 250.f;
class CVEHICLE {
private:
	int mX, mY;
public:
	virtual void Move(float, float) = 0;
	sf::Sprite sprite;
};

class CCAR : public CVEHICLE {
public:
	CCAR(); //load sprite tu texture o day
	CCAR(float x);
	void Move(float x, float y);
	void setPosition(float x, float y);


private:
	sf::Texture carTexture;

};
extern std::vector<CCAR> cars;
class CTRUCK : public CVEHICLE {
public:
	void Move(float x, float y);
};

extern std::vector<CCAR> generatedCars;
void generateCar(); //tao mot xe

void drawCar(sf::RenderWindow& window, std::vector<CCAR>& generatedCars);