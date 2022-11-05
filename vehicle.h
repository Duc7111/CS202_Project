#include "graphics.h"
#pragma once
class CVEHICLE {
	int mX, mY;
public:
	virtual void Move(float, float)=0;
};

class CCAR : public CVEHICLE {
public:
	CCAR(); //load sprite tu texture o day
	sf::Sprite carSprite;
	void Move(float x, float y);
	void setPosition(float x, float y);
	void moveInWindow(sf::Clock clock, sf::Time& elapsed, const sf::Time& update_ms);
	void drawCar(sf::RenderWindow& window);
private:
	sf::Texture carTexture;
};
extern std::vector<CCAR> cars;
class CTRUCK : public CVEHICLE {
public:
	void Move(float x, float y);
};


//void generateCar(sf::RenderWindow& window); //tao mot xe
//ta se tao vong lap de generate car nay sau khi xe truoc di duoc 20m

void checkShouldGenerate(sf::RenderWindow& window); //ktra co nen generate xe, dung thread