#include "vehicle.h"
#include "game.h"


float YCar = 150.f;
float YTruck = 400.f;

void CCAR::loadTexture(float x) {
	CVEHICLE::sprite = sf::Sprite(CGAME::carTexture);
	sf::Vector2u size = CGAME::carTexture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
	sprite.setPosition(x, YCar);
}
void CTRUCK::loadTexture(float x) {
	CVEHICLE::sprite = sf::Sprite(CGAME::truckTexture);
	sf::Vector2u size = CGAME::truckTexture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
	sprite.setPosition(x, YTruck);
}
sf::Sprite CCAR::getSprite() {
	return this->sprite;
}
sf::Sprite CTRUCK::getSprite() {
	return this->sprite;
}

void CVEHICLE::Move(float x, float y) {
	sprite.move(x, y);
}

void CVEHICLE::setPosition(float x, float y) {
	sprite.setPosition(sf::Vector2f(x, y));
}


void CVEHICLE::drawInWindow(sf::RenderWindow& window) {
	window.draw(this->sprite);
}

