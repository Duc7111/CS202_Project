#include "vehicle.h"
#include "game.h"
std::vector<CCAR> generatedCars;
std::vector<CCAR> cars;
CCAR::CCAR() //load sprite tu texture o day
{
	texture.loadFromFile("car.png");
	sprite = sf::Sprite(texture);
	sf::Vector2u size = texture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
	sprite.setPosition(10.f, YCar);
	//day vao vector chua cac xe da tao
}
CCAR::CCAR(float x) {
	texture.loadFromFile("car.png");
	sprite = sf::Sprite(texture);
	sf::Vector2u size = texture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
	sprite.setPosition(x, YCar);
}

CTRUCK::CTRUCK() {
	texture.loadFromFile("truck.png");
	sprite = sf::Sprite(texture);
	sf::Vector2u size = texture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
	sprite.setPosition(10.f, YTruck);
}
CTRUCK::CTRUCK(float x) {
	texture.loadFromFile("truck.png");
	sprite = sf::Sprite(texture);
	sf::Vector2u size = texture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
	sprite.setPosition(10.f, YTruck);
}
void CVEHICLE::Move(float x, float y) {
	sprite.move(x, y);
}

void CCAR::setPosition(float x, float y) {
	sprite.setPosition(sf::Vector2f(x, y));
}



void generateCar() {
	//newCar.setPosition(10.f, 250.f); //dat xe moi o vi tri ben trai
	//newCar.Move(); //bay gio lam ham move de di chuyen
	generatedCars.push_back(CCAR());
}





void drawCar(sf::RenderWindow& window, std::vector<CCAR>& generatedCars) {

	for (int i = 0; i < generatedCars.size(); i++) {
		float newX = generatedCars[i].sprite.getPosition().x + (speed * timeStep);
		if (newX > 1840)
			newX = setX;
		generatedCars[i].sprite.setPosition(newX, YCar);
	}

	/*if (newX == 20.f)
		generateCar();*/

	for (int i = 0; i < generatedCars.size(); i++) {
		if (generatedCars[i].sprite.getPosition().x > 1840) {
			generatedCars[i].sprite.setPosition(setX, YCar);
		}

	}

	window.clear(sf::Color(16, 16, 16, 255));
	for (CCAR car : generatedCars)
		window.draw(car.sprite);
}