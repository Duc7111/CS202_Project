
#pragma once
#include "graphics.h"
#include <SFML/Audio.hpp>

extern float YCar;
extern float YTruck;

class CGAME;
class CPEOPLE;

class CVEHICLE {
private:
	int mX, mY;
	sf::SoundBuffer hornBuffer;
	sf::Sound hornSound;
	bool isSetSound = false;

protected:
	sf::Vector2f currentPos;
	sf::Sprite sprite;
public:
	void Move(float x, float y);
	void setPosition(float x, float y);
	void drawInWindow(sf::RenderWindow& window);
	virtual void loadTexture(float x) = 0;
	virtual void loadTextureForeground(float x) = 0; //tao sprite cho background phu
	virtual sf::Sprite getSprite() = 0;
	virtual sf::Texture getTexture() = 0;
	virtual sf::Image getImage() = 0;
	virtual bool setTexture(std::string fileName) = 0;

	friend void scale(CVEHICLE*, float, float);

	virtual bool CollidedWithPlayer(CPEOPLE player) = 0;

	bool isCar;


	sf::Vector2f getCurrentPos();

	void horn();

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
	sf::Texture getTexture();
	sf::Image getImage();

	bool setTexture(std::string fileName);

	bool CollidedWithPlayer(CPEOPLE player);
};


class CTRUCK : public CVEHICLE {
private:

public:
	CTRUCK();
	/*CTRUCK(float x);*/
	void loadTexture(float x);
	sf::Sprite getSprite();

	void loadTextureForeground(float x);
	sf::Texture getTexture();
	sf::Image getImage();

	bool setTexture(std::string fileName);

	bool CollidedWithPlayer(CPEOPLE player);
};

class TRAFFICLIGHT {
private:
	sf::Texture texture[3];
public:
	TRAFFICLIGHT();
	sf::Sprite sprite;
	int status = 2;//mac dinh la den xanh

	void switchStatus(int newStatus);
	static bool isStopped; //ktra den xanh den do
};

