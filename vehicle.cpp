
#include "vehicle.h"
#include "game.h"
#include "people.h"
#include "settings.h"

float YCar = 150.f;
float YTruck = 400.f;

void CVEHICLE::horn() {
	if (Settings::isMuted)
		return;
	if (isSetSound == false) {
		if (!hornBuffer.loadFromFile("car.wav")) {
			cout << "Wrong location . File does not existed";
		}
		hornSound.setBuffer(hornBuffer);
		hornSound.setVolume(80.f);
		isSetSound = true;

		hornSound.play();

		cout << "horn";
	}

}
CCAR::CCAR() {
	CVEHICLE::isCar = true;

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
	CVEHICLE::isCar = false;

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
	if (this->side)
		x = -x;
	sf::Vector2f pos = sprite.getPosition();
	sprite.setPosition(pos.x + x, pos.y + y);
	currentPos = { sprite.getPosition().x,sprite.getPosition().y };
}
sf::Vector2f CVEHICLE::getCurrentPos() {
	return currentPos;
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


bool CCAR::setTexture(std::string fileName) {
	if (!CGAME::carTexture.loadFromFile(fileName))
		return false;
	return true;
}
bool CTRUCK::setTexture(std::string fileName) {
	if (!CGAME::truckTexture.loadFromFile(fileName))
		return false;
	return true;
}
bool CCAR::CollidedWithPlayer(CPEOPLE player) {
	return PixelPerfectCollision(sprite, player.getSprite(), CGAME::carImage, player.getImage());
}
bool CTRUCK::CollidedWithPlayer(CPEOPLE player) {
	return PixelPerfectCollision(sprite, player.getSprite(), CGAME::truckImage, player.getImage());
}