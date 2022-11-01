#include "graphics.h"
class CVEHICLE {
	int mX, mY;
public:
	virtual void Move(int, int);
	//...
};

class CCAR : public CVEHICLE {
public:
	CCAR(); //load sprite tu texture o day
	sf::Sprite carSprite;
private:
	sf::Texture carTexture;
};

class CTRUCK : public CVEHICLE {
public:
	//...
};