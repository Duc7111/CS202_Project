#include "vehicle.h"
#include "game.h"
std::vector<CCAR> generatedCars;
std::vector<CCAR> cars;

void CCAR::loadTexture(float x) {
	std::cout << "car load\n";
	CVEHICLE::texture.loadFromFile("car.png");
	CVEHICLE::sprite = sf::Sprite(CVEHICLE::texture);
	sf::Vector2u size = texture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
	sprite.setPosition(x, YCar);
}
void CTRUCK::loadTexture(float x) {
	std::cout << "truck load\n";
	CVEHICLE::texture.loadFromFile("truck.png");
	CVEHICLE::sprite = sf::Sprite(CVEHICLE::texture);
	sf::Vector2u size = texture.getSize();
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
sf::Texture CCAR::getTexture() {
	return this->texture;
}
sf::Texture CTRUCK::getTexture() {
	return this->texture;
}
//CCAR::CCAR() //load sprite tu texture o day
//{
//	loadTexture();
//	//day vao vector chua cac xe da tao
//}
//CCAR::CCAR(float x) {
//	/*texture.loadFromFile("car.png");
//	sprite = sf::Sprite(texture);
//	sf::Vector2u size = texture.getSize();
//	sprite.setOrigin(size.x / 2, size.y / 2);
//	sf::Vector2f increment(0.4f, 0.4f);
//	sprite.scale(sf::Vector2f(0.25f, 0.25f));
//	sprite.setPosition(x, YCar);*/
//
//	loadTexture(x);
//}
//
//CTRUCK::CTRUCK() {
//	texture.loadFromFile("truck.png");
//	sprite = sf::Sprite(texture);
//	sf::Vector2u size = texture.getSize();
//	sprite.setOrigin(size.x / 2, size.y / 2);
//	sf::Vector2f increment(0.4f, 0.4f);
//	sprite.scale(sf::Vector2f(0.25f, 0.25f));
//	sprite.setPosition(10.f, YTruck);
//}
//CTRUCK::CTRUCK(float x) {
//	texture.loadFromFile("truck.png");
//	sprite = sf::Sprite(texture);
//	sf::Vector2u size = texture.getSize();
//	sprite.setOrigin(size.x / 2, size.y / 2);
//	sf::Vector2f increment(0.4f, 0.4f);
//	sprite.scale(sf::Vector2f(0.25f, 0.25f));
//	sprite.setPosition(x, YTruck);
//}
void CVEHICLE::Move(float x, float y) {
	sprite.move(x, y);
}

void CVEHICLE::setPosition(float x, float y) {
	sprite.setPosition(sf::Vector2f(x, y));
}

void generateCar() {
	//newCar.setPosition(10.f, 250.f); //dat xe moi o vi tri ben trai
	//newCar.Move(); //bay gio lam ham move de di chuyen
	generatedCars.push_back(CCAR());
}


void CVEHICLE::drawInWindow(sf::RenderWindow& window) {
	window.draw(this->sprite);
}