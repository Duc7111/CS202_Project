
#include "vehicle.h"
#include "game.h"

float YCar = 150.f;
float YTruck = 400.f;


CCAR::CCAR() {
	CVEHICLE::sprite = sf::Sprite(CGAME::carTexture);
	sf::Vector2u size = CGAME::carTexture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));


}
void CCAR::loadTexture(float x) {

	sprite.setPosition(x, YCar);


}
void CCAR::loadTextureForeground(float x) {
	loadTexture(x);
	sprite.setPosition(x, YCar - moveOffset - 150);
}
CTRUCK::CTRUCK() {
	CVEHICLE::sprite = sf::Sprite(CGAME::truckTexture);
	sf::Vector2u size = CGAME::truckTexture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));


}
void CTRUCK::loadTexture(float x) {

	sprite.setPosition(x, YTruck);


}
void CTRUCK::loadTextureForeground(float x) {
	loadTexture(x);
	sprite.setPosition(x, YTruck - moveOffset - 150);
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



sf::Texture CCAR::getTexture() {
	return CGAME::carTexture;
}

sf::Texture CTRUCK::getTexture() {
	return CGAME::truckTexture;
}
sf::Image CCAR::getImage() {
	return CGAME::carImage;
}
sf::Image CTRUCK::getImage() {
	return CGAME::truckImage;
}

TRAFFICLIGHT::TRAFFICLIGHT() {
	texture[0].loadFromFile("trafficLight/red.png");
	texture[1].loadFromFile("trafficLight/yellow.png");
	texture[2].loadFromFile("trafficLight/green.png");
	status = 2;
	sprite = sf::Sprite(texture[status]);
}

void TRAFFICLIGHT::switchStatus(int newStatus) {
	sprite = sf::Sprite(texture[newStatus]);

}