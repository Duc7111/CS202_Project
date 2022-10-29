#include "graphics.h"
sf::Texture texture;
sf::Sprite sprite;
void loadTexture() {
	texture.loadFromFile("car.png");
	texture.setSmooth(true); //lam diu texture
	sprite.setTexture(texture); //tao sprite
	sprite.setColor(sf::Color(0, 255, 0));
}
