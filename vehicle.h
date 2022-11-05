#include "graphics.h"
#pragma once
const float Y = 250.f;
class CVEHICLE {
	int mX, mY;
public:
	virtual void Move(float, float) = 0;
};

class CCAR : public CVEHICLE {
public:
	CCAR(); //load sprite tu texture o day
	CCAR(float x);
	sf::Sprite carSprite;
	void Move(float x, float y);
	void setPosition(float x, float y);

	/*void drawCar(sf::RenderWindow& window, sf::Clock clock, sf::Time& elapsed, const sf::Time& update_ms);*/

private:
	sf::Texture carTexture;
	/*void moveInWindow(sf::Clock clock, sf::Time& elapsed, const sf::Time& update_ms);*/
};
extern std::vector<CCAR> cars;
class CTRUCK : public CVEHICLE {
public:
	void Move(float x, float y);
};

extern std::vector<CCAR> generatedCars;
void generateCar(); //tao mot xe
//ta se tao vong lap de generate car nay sau khi xe truoc di duoc 20m

//void checkShouldGenerate(sf::RenderWindow& window); //ktra co nen generate xe, dung thread

void drawCar(sf::RenderWindow& window, std::vector<CCAR>& generatedCars);