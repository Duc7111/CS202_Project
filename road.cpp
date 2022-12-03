#include "road.h"
#include <iostream>

Road::Road() : status(false){}


void Road::setPosition(float y)
{
	sprite.setPosition(sf::Vector2f(0.f, y));
}

CVEHICLE* VehicleRoad::VehicleFactory()
{
	
}

VehicleRoad::VehicleRoad() : v(0) {}

VehicleRoad::~VehicleRoad()
{
	while (!vQueue.isEmpty()) delete vQueue.pop();
}

bool VehicleRoad::loadTexture(std::string fileName)
{
	if(!texture[0].loadFromFile(fileName)) return false;
}

void VehicleRoad::resetSprite()
{
	sprite.setTexture(texture[0]);
	float scale = (float)M_CELL / sprite.getScale().y;
	sprite.setScale(sf::Vector2f(scale, scale));
	sprite.setOrigin(sf::Vector2f(0.f, (float)M_CELL / 2));
}

void VehicleRoad::setPosition(float y)
{
	Road::setPosition(y);
	traficLight.shape.setPosition(sf::Vector2f(1280, y + (float)M_CELL/2));

	while (!vQueue.isEmpty()) delete vQueue.pop();
	vQueue.front = 0;
}

void VehicleRoad::run()
{
	
}

void VehicleRoad::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	for (int i = vQueue.front; i < vQueue.size; ++i)
		vQueue.arr[i]->drawInWindow(window);
	window.draw(traficLight.shape);
}

CANIMAL* AnimalRoad::AnimalFactory()
{

}

AnimalRoad::AnimalRoad() : v(0) {}

AnimalRoad::~AnimalRoad()
{
	while (!aQueue.isEmpty()) delete aQueue.pop();
}

bool AnimalRoad::loadTexture(std::string fileName)
{
	return texture[1].loadFromFile(fileName);
}

void AnimalRoad::resetSprite()
{
	sprite.setTexture(texture[1]);
	float scale = (float)M_CELL / sprite.getScale().y;
	sprite.setScale(sf::Vector2f(scale, scale));
	sprite.setOrigin(sf::Vector2f(0.f, (float)M_CELL / 2));
}

void AnimalRoad::setPosition(float y)
{
	Road::setPosition(y);

	while (!aQueue.isEmpty()) delete aQueue.pop();
	aQueue.front = 0;
}

void AnimalRoad::run()
{

}

void AnimalRoad::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	for (int i = aQueue.front; i < aQueue.size; i = (i+1)%OBJ_MAX)
		aQueue.arr[i]->drawInWindow(window);
}