#pragma once

#include "vehicle.h"
#include "animal.h"
#include "position.h"

#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <string>

class Road {
protected:
	static sf::Texture texture[2];

	sf::Sprite sprite;
public:
	Road();

	bool status;

	virtual void setPosition(float y);
	virtual void resetSprite() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};

#define OBJ_MAX 5

template<class T>
struct ObjQueue //built only for Road
{
	T arr[OBJ_MAX] = default;
	int front, size;

	ObjQueue() : front(0), size(0) {}

	bool isEmpty()
	{
		if (size == 0) return true;
		return false;
	}

	void push(T)
	{
		if (size == OBJ_MAX) return;
		++size;
		front = (front - 1) % OBJ_MAX;
		arr[front] = T;
	}
	T& pop() //check isEmpty before calling
	{
		return arr[(front + size--)%OBJ_MAX];
	}
};

class VehicleRoad : public Road
{
private:
	struct TF
	{
		bool status;//true: green, false: red
		sf::RectangleShape shape;

		TF() : status(true), shape(sf::Vector2f(M_CELL/10, M_CELL/10))
		{
			shape.setFillColor(sf::Color::Green);
		}

		void function(){}
	}traficLight;

	float v;
	ObjQueue<CVEHICLE*> vQueue;

	CVEHICLE* VehicleFactory();

public:
	VehicleRoad();
	~VehicleRoad();

	static bool loadTexture(std::string fileName);

	void resetSprite();
	void setPosition(float y);
	void run();
	void draw(sf::RenderWindow& window);
};

class AnimalRoad : public Road
{
private:
	float v;
	ObjQueue<CANIMAL*> aQueue;

	CANIMAL* AnimalFactory();

public:
	AnimalRoad();
	~AnimalRoad();

	static bool loadTexture(std::string fileName);

	void resetSprite();
	void setPosition(float y);
	void run();
	void draw(sf::RenderWindow& window);
};