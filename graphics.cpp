#include "graphics.h"
#include <iostream>
sf::Texture texture;
sf::Sprite sprite;
void loadTexture() {
	if (!texture.loadFromFile("car.png"))
		std::cout<<"Fail to load";
	texture.setSmooth(true); //lam diu texture
	sprite.setTexture(texture); //tao sprite
	//sprite.setColor(sf::Color(0, 255, 0));
}
