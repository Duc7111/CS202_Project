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
private:
	sf::Texture carTexture;
};

class CTRUCK : public CVEHICLE {
public:
	void Move(int, int);
};