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