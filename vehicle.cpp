#include "vehicle.h"
CCAR::CCAR() //load sprite tu texture o day
{
	carTexture.loadFromFile("car.png");
	carSprite = sf::Sprite(carTexture);
	sf::Vector2u size = carTexture.getSize();
	carSprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);
	carSprite.scale(sf::Vector2f(0.25f, 0.25f));
	carSprite.setPosition(10.f, Y);
	//day vao vector chua cac xe da tao
}
CCAR::CCAR(float x) {
	carTexture.loadFromFile("car.png");
	carSprite = sf::Sprite(carTexture);
	sf::Vector2u size = carTexture.getSize();
	carSprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);
	carSprite.scale(sf::Vector2f(0.25f, 0.25f));
	carSprite.setPosition(x, Y);
}
void CCAR::Move(float x, float y) {
	carSprite.move(x, y);
}

void CCAR::setPosition(float x, float y) {
	carSprite.setPosition(sf::Vector2f(x, y));
}

std::vector<CCAR> cars;

void generateCar() {
	//newCar.setPosition(10.f, 250.f); //dat xe moi o vi tri ben trai
	//newCar.Move(); //bay gio lam ham move de di chuyen
	generatedCars.push_back(CCAR());
}



std::vector<CCAR> generatedCars;
const float setX = -500;
const float speed = 0.005f;
void drawCar(sf::RenderWindow& window, sf::Clock clock, sf::Time& elapsed, const sf::Time& update_ms, std::vector<CCAR>& generatedCars) {
	elapsed += clock.restart();

	while (elapsed >= update_ms) {
		for (int i = 0; i < generatedCars.size(); i++) {
			float newX = generatedCars[i].carSprite.getPosition().x + (speed * elapsed.asSeconds());
			if (newX > 1840)
				newX = setX;
			generatedCars[i].carSprite.setPosition(newX, Y);
		}
		elapsed -= update_ms;

		/*if (newX == 20.f)
			generateCar();*/

		for (int i = 0; i < generatedCars.size(); i++) {
			if (generatedCars[i].carSprite.getPosition().x > 1840) {
				generatedCars[i].carSprite.setPosition(setX, Y);
			}

		}
	}
	window.clear(sf::Color(16, 16, 16, 255));
	for (CCAR car : generatedCars)
		window.draw(car.carSprite);
}