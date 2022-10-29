#include "graphics.h"
#include <SFML/Graphics.hpp>
sf::Sprite loadTextures() {
	texture.loadFromFile("Sprite\\car.png");
	texture.setSmooth(true); //lam diu texture
	sf::Sprite sprite;
	sprite.setTexture(texture); //tao sprite
	return sprite;
}
