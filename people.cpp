#include "people.h"

void CPEOPLE::loadTexture() {
	texture[0].loadFromFile("player_front.png");
	texture[1].loadFromFile("player_back.png");
	texture[2].loadFromFile("player_right.png");
	texture[3].loadFromFile("player_left.png");
	sprite.setTexture(texture[0]);
}

void CPEOPLE::drawInWindow(sf::RenderWindow& window)
{
}

sf::Vector2i CPEOPLE::getPosition() {
	return sf::Vector2i(mX, mY);
}

