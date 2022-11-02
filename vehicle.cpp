#include "vehicle.h"
CCAR::CCAR() //load sprite tu texture o day
{
	carTexture.loadFromFile("car.png");
	carSprite = sf::Sprite(carTexture);
	sf::Vector2u size = carTexture.getSize();
	carSprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);
	carSprite.scale(sf::Vector2f(0.25f, 0.25f));
}
void CCAR::Move(int, int) {

}
void CCAR::setPosition(float x, float y) {
	carSprite.setPosition(sf::Vector2f(x, y));
}

std::vector<CCAR> cars;

void generateCar(sf::RenderWindow& window) {
	CCAR newCar;
	newCar.setPosition(0.f, 250.f); //dat xe moi o vi tri ben trai
	window.draw(newCar.carSprite);
	//newCar.Move(); //bay gio lam ham move de di chuyen
}

void checkShouldGenerate(sf::RenderWindow& window) //ktra co nen generate xe, dung thread
{
	CCAR latestCar = cars.back();
	if (latestCar.carSprite.getPosition().x == 20.f) {
		generateCar(window);
	}
}