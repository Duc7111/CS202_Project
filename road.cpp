#include "road.h"
#include <iostream>

ROAD::ROAD() {
	texture.loadFromFile("road.png");
	sprite = sf::Sprite(texture);
	sf::Vector2u size = texture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
}
void ROAD::loadTexture(float y) {


	sprite.setPosition(0, y);
}

bool ROAD::loadTexture(std::string fileName)
{
	return texture.loadFromFile(fileName);
}

void ROAD::setPosition(float y)
{
	sprite.setPosition(sf::Vector2f(0.f, y));
}

void ROAD::drawRoad(sf::RenderWindow& window) {
	window.draw(sprite);
}

void GRASS::loadTexture(float y) {
	texture.loadFromFile("grass.png");
	sprite = sf::Sprite(texture);
	sf::Vector2u size = texture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
	sprite.setPosition(0, y);
}

DIRT::DIRT() {
	texture.loadFromFile("dirt.png");
	sprite = sf::Sprite(texture);
	sf::Vector2u size = texture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.setScale(1000, 0.6f);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
}
void DIRT::loadTexture(float y) {


	sprite.setPosition(0, y);
}

CVEHICLE* VehicleRoad::VehicleFactory(float y)
{
	
}

VehicleRoad::VehicleRoad(float velocity) : v(velocity), ROAD(), front(0), end(0)
{
	for (int i = 0; i < OBJ_MAX; ++i) a[i] = nullptr;
}

VehicleRoad::~VehicleRoad()
{
	for (int i = 0; i < OBJ_MAX; ++i) delete a[i];
}

bool VehicleRoad::loadTexture(std::string fileName)
{
	if(!texture.loadFromFile(fileName)) return false;
	return traficLight.setTexture("greenLight.png", "redLight.png");
}

void VehicleRoad::run()
{

}

AnimalRoad::AnimalRoad()
{
	for (int i = 0; i < OBJ_MAX; ++i) a[i] = nullptr;
}

AnimalRoad::~AnimalRoad()
{
	for (int i = 0; i < OBJ_MAX; ++i) delete a[i];
}

bool AnimalRoad::loadTexture(std::string fileName)
{
	return ROAD::loadTexture(fileName);
}

void AnimalRoad::run()
{

}