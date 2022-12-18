#include "road.h"
#include "people.h"
#include <iostream>
#include "effect.h"

#define WINDOW (*windowHandle)

sf::RenderWindow* Road::windowHandle = nullptr;
sf::Texture Road::texture[];

void scale(CVEHICLE* v, float x, float y)
{
	v->sprite.scale(x, y);
}

void scale(CANIMAL* a, float x, float y)
{
	a->sprite.scale(x, y);
}

Road::Road() : side(DICE::flip()) {}

void Road::setWindow(sf::RenderWindow* window)
{
	windowHandle = window;
}

void Road::setPosition(float y)
{
	sprite.setPosition(sf::Vector2f(0.f, ((6.0f - y) / 7.0f) * 700));
}

void Road::drawRoad()
{
	WINDOW.draw(sprite);
}

/////////////////////////////////////////////////////

CVEHICLE* VehicleRoad::VehicleFactory()
{
	CVEHICLE* vehicle;
	// Type
	if (DICE::flip()) vehicle = new CCAR;
	else vehicle = new CTRUCK;
	//side
	if (side) scale(vehicle, -1.f, 1.f);
	//position
	float x;
	if (vQueue.isEmpty()) x = 10.f;
	else x = abs(vQueue[0]->getTexture().getSize().x * vQueue[0]->getSprite().getScale().x) + 20.f;

	if (side)
		x = DICE::random(WINDOW.getSize().x + x, WINDOW.getSize().x + 5 * x);
	else
		x = DICE::random(-x * 5, -x);

	vehicle->setPosition(x, sprite.getPosition().y + 20);
	return vehicle;
}

bool VehicleRoad::checkCollide(sf::RenderWindow& window, CPEOPLE player) {
	//sẽ tối ưu hơn bằng cách chỉ check những xe nào trong phạm vi của người chơi
	for (int i = 0; i < vQueue.size(); i++) {
		if (IsNearby(player, vQueue[i]->getSprite(), 5))
			if (vQueue[i]->CollidedWithPlayer(player)) {
				explosion::animateExplosion(window, vQueue[i]->getSprite().getPosition());
				return true;
			}
	}
	return false;
}

VehicleRoad::VehicleRoad() : v(0) {}

VehicleRoad::~VehicleRoad()
{
	for (int i = vQueue.size() - 1; i > -1; --i) delete vQueue[i];
}

bool VehicleRoad::loadTexture()
{
	if (!texture[0].loadFromFile("road1.png")) return false;
	return true;
}

void VehicleRoad::resetSprite()
{
	sprite.setTexture(texture[0]);
	float scale = (float)M_CELL / (sprite.getTexture()->getSize().y);
	sprite.setScale(sf::Vector2f(scale, scale));
	sprite.setOrigin(sf::Vector2f(0.f, (float)M_CELL / 2));
}

void VehicleRoad::setPosition(float y)
{
	// Road position
	Road::setPosition(y);
	// traficLight position
	if (side) traficLight.shape.setPosition(sf::Vector2f(20.f, Road::sprite.getPosition().y));
	else traficLight.shape.setPosition(sf::Vector2f(WINDOW.getSize().x - 20.f, Road::sprite.getPosition().y));
	// Reset queue
	for (int i = vQueue.size() - 1; i > -1; --i) delete vQueue[i];
	vQueue.reset();
}

void VehicleRoad::setVelocity(float velocity)
{
	if (!side) v = velocity;
	else v = -velocity;
}

void VehicleRoad::run()
{
	// Trafic light
	traficLight.function();
	if (!traficLight.status) return;
	// New vehicle
	if (vQueue.size() == 0 || (vQueue.size() < OBJ_MAX && vQueue[0]->getSprite().getPosition().x > 0 && vQueue[0]->getSprite().getPosition().x < WINDOW.getSize().x + 20.f))
		vQueue.push(VehicleFactory());
	// Vehicles
	if ((side && vQueue[vQueue.size() - 1]->getSprite().getPosition().x < -50.f)
		|| (!side && vQueue[vQueue.size() - 1]->getSprite().getPosition().x > WINDOW.getSize().x + 50.f))
		delete vQueue.pop();

	for (int i = vQueue.size() - 1; i > -1; --i)
		vQueue[i]->Move(v, 0);
}

void VehicleRoad::drawObj()
{
	for (int i = 0; i < vQueue.size(); ++i)
		vQueue[i]->drawInWindow(WINDOW);
	WINDOW.draw(traficLight.shape);
}

////////////////////////////////////////////////////////

bool AnimalRoad::checkCollide(sf::RenderWindow& window, CPEOPLE player) {
	return false;
}

CANIMAL* AnimalRoad::AnimalFactory()
{
	CANIMAL* animal;
	// Type
	if (DICE::flip()) animal = new CDINAUSOR;
	else animal = new CBIRD;
	//side
	if (side) scale(animal, -1.f, 1.f);
	//position
	float x;
	if (aQueue.isEmpty()) x = 10.f;
	else x = abs(aQueue[0]->getTexture().getSize().x * aQueue[0]->getSprite().getScale().x) + 20.f;

	if (side)
		x = DICE::random(WINDOW.getSize().x + x, WINDOW.getSize().x + 5 * x);
	else
		x = DICE::random(-x * 5, -x);

	animal->setPosition(x, sprite.getPosition().y);
	return animal;
}

AnimalRoad::AnimalRoad() : v(0) {}

AnimalRoad::~AnimalRoad()
{
	while (!aQueue.isEmpty()) delete aQueue.pop();
}

bool AnimalRoad::loadTexture()
{
	return texture[1].loadFromFile("road2.png");
}

void AnimalRoad::resetSprite()
{
	sprite.setTexture(texture[1]);
	float scale = (float)M_CELL / (sprite.getTexture()->getSize().y);
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

void AnimalRoad::setVelocity(float velocity)
{
	if (!side) v = velocity;
	else v = -velocity;
}

void AnimalRoad::run()
{
	// New animal
	if (aQueue.size() == 0 || (aQueue.size() < OBJ_MAX && aQueue[0]->getSprite().getPosition().x > 0 && aQueue[0]->getSprite().getPosition().x < WINDOW.getSize().x + 20.f))
		aQueue.push(AnimalFactory());
	// Animals
	if ((side && aQueue[aQueue.size() - 1]->getSprite().getPosition().x < -50.f)
		|| (!side && aQueue[aQueue.size() - 1]->getSprite().getPosition().x > WINDOW.getSize().x + 50.f))
		delete aQueue.pop();

	for (int i = aQueue.size() - 1; i > -1; --i)
		aQueue[i]->Move(v, 0);
}

void AnimalRoad::drawObj()
{
	for (int i = aQueue.size() - 1; i > -1; --i)
		aQueue[i]->drawInWindow(WINDOW);
}