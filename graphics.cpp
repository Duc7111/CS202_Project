#include "graphics.h"
sf::Texture texture;
sf::Sprite loadTexture() {
	texture.loadFromFile("Sprite\\car.png");
	texture.setSmooth(true); //lam diu texture
	sf::Sprite sprite;
	sprite.setTexture(texture); //tao sprite
	return sprite;
}
