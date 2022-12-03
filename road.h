#pragma once

#include "vehicle.h"
#include "animal.h"

#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <string>

class ROAD {
protected:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	bool status;

	ROAD();
	void loadTexture(float y);
	bool loadTexture(std::string fileName);
	void setPosition(float y);
	void drawRoad(sf::RenderWindow& window);
};

class GRASS : public ROAD {
public:
	void loadTexture(float y); //overload cai cua thang Grass
};

class DIRT : public ROAD {
public:
	DIRT();
	void loadTexture(float y);
};


//NEW ROAD - USE THESE

#define OBJ_MAX 5

class VehicleRoad : public ROAD
{
private:
	struct TF
	{
		bool status;//true: green, false: red

		sf::Sprite sprite;
		sf::Texture G, R;

		TF() : status(true) {}

		void function(){}
		bool setTexture(std::string greenLight, std::string redLight){}
	}traficLight;

	float v;
	int front, end;
	CVEHICLE* a[OBJ_MAX];

	static CVEHICLE* VehicleFactory(float y);

public:
	VehicleRoad(float velocity);
	~VehicleRoad();

	bool loadTexture(std::string fileName);
	using ROAD::setPosition;
	void run();
};

class AnimalRoad : public ROAD
{
private:
	float v;
	int front, end;
	CANIMAL* a[OBJ_MAX];

	static CANIMAL* AnimalFactory(float y);

public:
	AnimalRoad();
	~AnimalRoad();

	bool loadTexture(std::string fileName);
	using ROAD::setPosition;
	void run();
};