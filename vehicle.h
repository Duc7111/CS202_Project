#include "graphics.h"
#pragma once
class CVEHICLE {
	int mX, mY;
public:
	virtual void Move(int, int)=0;
};

class CCAR : public CVEHICLE {
public:
	CCAR(); //load sprite tu texture o day
	sf::Sprite carSprite;
	void Move(int, int);
	void setPosition(float x, float y);
private:
	sf::Texture carTexture;
};
extern std::vector<CCAR> cars;
class CTRUCK : public CVEHICLE {
public:
	void Move(int, int);
};


void generateCar(sf::RenderWindow& window); //tao mot xe
//ta se tao vong lap de generate car nay sau khi xe truoc di duoc 20m

void checkShouldGenerate(sf::RenderWindow& window); //ktra co nen generate xe, dung thread