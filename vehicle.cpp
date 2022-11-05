#include "vehicle.h"
CCAR::CCAR() //load sprite tu texture o day
{
	carTexture.loadFromFile("car.png");
	carSprite = sf::Sprite(carTexture);
	sf::Vector2u size = carTexture.getSize();
	carSprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);
	carSprite.scale(sf::Vector2f(0.25f, 0.25f));
	carSprite.setPosition(10.f, 250.f);
	//day vao vector chua cac xe da tao
}
CCAR::CCAR(float x) {
	carTexture.loadFromFile("car.png");
	carSprite = sf::Sprite(carTexture);
	sf::Vector2u size = carTexture.getSize();
	carSprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);
	carSprite.scale(sf::Vector2f(0.25f, 0.25f));
	carSprite.setPosition(x, 250.f);
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

//void CCAR::drawCar(sf::RenderWindow& window, sf::Clock clock, sf::Time& elapsed, const sf::Time& update_ms) {
//	moveInWindow(clock, elapsed, update_ms);
//	window.clear(sf::Color(16, 16, 16, 255));
//	window.draw(this->carSprite);
//}
//void CCAR::moveInWindow(sf::Clock clock, sf::Time& elapsed, const sf::Time& update_ms) {
//
//    elapsed += clock.restart();
//    while (elapsed >= update_ms) {
//		float newX = this->carSprite.getPosition().x + 0.01f;
//		float currentY = this->carSprite.getPosition().y;
//		this->carSprite.setPosition(newX, currentY);
//
//        elapsed -= update_ms;
//
//		if (newX == 20.f)
//			generateCar();
//    }
//}

std::vector<CCAR> generatedCars;

void drawCar(sf::RenderWindow& window, sf::Clock clock, sf::Time& elapsed, const sf::Time& update_ms, std::vector<CCAR>& generatedCars) {
	elapsed += clock.restart();
	while (elapsed >= update_ms) {
		for (int i = 0; i < generatedCars.size(); i++) {
			float newX = generatedCars[i].carSprite.getPosition().x + 0.01f;
			float currentY = generatedCars[i].carSprite.getPosition().y;
			generatedCars[i].carSprite.setPosition(newX, currentY);
		}
		//float newX = generatedCars[0].carSprite.getPosition().x + 0.01f;
		//float currentY = generatedCars[0].carSprite.getPosition().y;
		//generatedCars[0].carSprite.setPosition(newX, currentY);

		//newX = generatedCars[1].carSprite.getPosition().x + 0.01f;
		//currentY = generatedCars[1].carSprite.getPosition().y;
		//generatedCars[1].carSprite.setPosition(newX, currentY);
		elapsed -= update_ms;

		/*if (newX == 20.f)
			generateCar();*/
	}
	window.clear(sf::Color(16, 16, 16, 255));
	for (CCAR car : generatedCars)
		window.draw(car.carSprite);
}