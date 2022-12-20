#pragma once
#include <SFML/Graphics.hpp>
#include "vehicle.h"
#include "animal.h"
#include "position.h"
#include "dice.h"
#include <random>
#include <time.h>
#include <string>

class CPEOPLE;

class Road {
protected:
	static sf::RenderWindow* windowHandle;
	static sf::Texture texture[2];


	bool side; //left: false,  right: true
public:
	Road();
	sf::Sprite sprite;

	static void setWindow(sf::RenderWindow* windowHandle);

	virtual void resetSprite() = 0;

	virtual void setPosition(float y) = 0;
	virtual void setVelocity(float velocity) = 0;

	virtual void run() = 0;

	virtual bool checkCollide(sf::RenderWindow& window, CPEOPLE player) = 0;

	void drawRoad();
	virtual void drawObj() = 0;

	bool isVehicleRoad;
	int index;
};

#define OBJ_MAX 5

template<class T>
class ObjQueue //built only for Road
{
private:
	T arr[OBJ_MAX]; // = default;
	int front, size_v;

public:
	ObjQueue() : front(0), size_v(0) {}

	bool isEmpty()
	{
		if (size_v == 0) return true;
		return false;
	}
	int size()
	{
		return size_v;
	}

	void push(T value)
	{
		if (size_v == OBJ_MAX) return;
		++size_v;
		if (front == 0) front = OBJ_MAX;
		front = front - 1;
		arr[front] = value;
	}
	T& pop() //check isEmpty before calling
	{
		return arr[(front + --size_v) % OBJ_MAX];
	}

	void reset()
	{
		front = OBJ_MAX;
		size_v = 0;
	}

	T& operator[](int i)
	{
		return arr[(front + i) % OBJ_MAX];
	}
};

class VehicleRoad : public Road
{
private:
	struct TF
	{
		bool status;//true: green, false: red
		sf::RectangleShape shape;
		sf::Clock clock;

		TF() : status(true), shape(sf::Vector2f(M_CELL / 10, M_CELL / 10))
		{
			shape.setFillColor(sf::Color::Green);
		}

		void function()
		{
			sf::Time time = clock.getElapsedTime();
			if (time.asSeconds() >= 3.f)
			{
				status = !status;
				if (status) shape.setFillColor(sf::Color::Green);
				else shape.setFillColor(sf::Color::Red);
				clock.restart();
			}
		}
	}traficLight;

	float v;
	ObjQueue<CVEHICLE*> vQueue;

	CVEHICLE* VehicleFactory();

public:
	VehicleRoad();
	~VehicleRoad();

	static bool loadTexture();

	void resetSprite();

	void setPosition(float y);
	void setVelocity(float velocity);

	void run();
	void drawObj();
	bool checkCollide(sf::RenderWindow& window, CPEOPLE player);
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

	static bool loadTexture();

	void resetSprite();

	void setPosition(float y);
	void setVelocity(float velocity);

	void run();
	void drawObj();
	bool checkCollide(sf::RenderWindow& window, CPEOPLE player);
};

bool isVehicleRoad(Road* ptr);

class TREE {
private:
	sf::Sprite sprite;

public:
	TREE();
	sf::Sprite getSprite();
	static void loadTexture();
	static sf::Texture texture[4];
	void drawInWindow(sf::RenderWindow& window);
};