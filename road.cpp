#include "road.h"

#include <iostream>

#define WINDOW (*windowHandle)

sf::RenderWindow* Road::windowHandle = nullptr;
sf::Texture Road::texture[];

Road::Road() : status(false){}

void Road::setWindow(sf::RenderWindow* window)
{
	windowHandle = window;
}

void Road::setPosition(float y)
{
	sprite.setPosition(sf::Vector2f(0.f, y));
}

/////////////////////////////////////////////////////

CVEHICLE* VehicleRoad::VehicleFactory()
{
	CVEHICLE* vehicle;
	// Type
	if (DICE::flip()) vehicle = new CCAR;
	else vehicle = new CTRUCK;
	//position
	float x = vQueue[0]->getTexture().getSize().x* vQueue[0]->getSprite().getScale().x + 10.f;
	x = DICE::random(-x * 5, -x);

	vehicle->setPosition(x, sprite.getPosition().y);
	return vehicle;
}

VehicleRoad::VehicleRoad() : v(0) {}

VehicleRoad::~VehicleRoad()
{
	for (int i = vQueue.size() - 1; i > -1; --i) delete vQueue[i];
}

bool VehicleRoad::loadTexture(std::string fileName)
{
	if(!texture[0].loadFromFile(fileName)) return false;
	return true;
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
	// Road position
	Road::setPosition(y);
	// traficLight position
	traficLight.shape.setPosition(sf::Vector2f(WINDOW.getSize().x - 20.f, y + (float)M_CELL / 2));
	// Reset queue
	for (int i = vQueue.size() - 1; i > -1; --i) delete vQueue[i];
	vQueue.reset();
}

void VehicleRoad::run()
{
	// Check condition
	if (!status)
	{
		traficLight.clock.restart();
		return;
	}
	// Trafic light
	traficLight.function();
	if (!traficLight.status) return;
	// Vehicles
	if (vQueue[vQueue.size() - 1]->getSprite().getPosition().x > WINDOW.getSize().x + 50.f)
		delete vQueue.pop();
	for (int i = vQueue.size() - 1; i > -1; --i)
		vQueue[i]->Move(v, 0);
	// New vehicle
	if (vQueue.size() == 0 || (vQueue.size() < OBJ_MAX && vQueue[0]->getSprite().getPosition().x < 0))
		vQueue.push(VehicleFactory());
}

void VehicleRoad::draw()
{
	WINDOW.draw(sprite);
	for (int i = 0; i < vQueue.size(); ++i)
		vQueue[i]->drawInWindow(WINDOW);
	WINDOW.draw(traficLight.shape);
}

////////////////////////////////////////////////////////

CANIMAL* AnimalRoad::AnimalFactory()
{
	CANIMAL* animal;
	// Type
	if (DICE::flip()) animal = new CDINAUSOR;
	else animal = new CBIRD;
	//position
	float x = aQueue[0]->getTexture().getSize().x * aQueue[0]->getSprite().getScale().x + 10.f;
	x = DICE::random(-x * 5, -x);

	animal->setPosition(x, sprite.getPosition().y);
	return animal;
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
	// Road position
	Road::setPosition(y);
	// Reset queue
	for (int i = aQueue.size() - 1; i > -1; --i) delete aQueue[i];
	aQueue.reset();
}

void AnimalRoad::run()
{
	// Check condition
	if (!status) return;
	// Vehicles
	if (aQueue[aQueue.size() - 1]->getSprite().getPosition().x > WINDOW.getSize().x + 50.f)
		delete aQueue.pop();
	for (int i = aQueue.size() - 1; i > -1; --i)
		aQueue[i]->Move(v, 0);
	// New animal
	if (aQueue.size() == OBJ_MAX || DICE::random(-2, 2)) return;
	aQueue.push(AnimalFactory());
}

void AnimalRoad::draw()
{
	WINDOW.draw(sprite);
	for (int i = aQueue.size() - 1; i > -1; --i)
		aQueue[i]->drawInWindow(WINDOW);
}