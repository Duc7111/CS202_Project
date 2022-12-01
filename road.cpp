#include "road.h"
#include <iostream>

ROAD::ROAD() {
	texture.loadFromFile("road.png");
	sprite = sf::Sprite(texture);
	sf::Vector2u size = texture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
}
void ROAD::loadTexture(float y) {
	std::cout << "road load\n";

	sprite.setPosition(0, y);
}

void ROAD::drawRoad(sf::RenderWindow& window) {
	window.draw(sprite);
}

void GRASS::loadTexture(float y) {
	std::cout << "grass load\n";
	texture.loadFromFile("grass.png");
	sprite = sf::Sprite(texture);
	sf::Vector2u size = texture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
	sprite.setPosition(0, y);
}

DIRT::DIRT() {
	texture.loadFromFile("dirt.png");
	sprite = sf::Sprite(texture);
	sf::Vector2u size = texture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.setScale(1000, 0.6f);
	sprite.scale(sf::Vector2f(0.25f, 0.25f));
}
void DIRT::loadTexture(float y) {
	std::cout << "dirt load\n";

	sprite.setPosition(0, y);
}