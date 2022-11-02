#include "graphics.h"
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

class CTRUCK : public CVEHICLE {
public:
	void Move(int, int);
};

extern std::vector<CCAR> cars;
void generateCar(); //tao mot xe
//ta se tao vong lap de generate car nay sau khi xe truoc di duoc 20m

void checkShouldGenerate(); //ktra co nen generate xe, dung thread