#include "effect.h"
#include<windows.h>
std::vector<sf::Texture> explosionTextures;

void explosion::loadTexture() {
	for (int i = 0; i < 8; i++) {
		sf::Texture temp;
		std::string path = explosionPath + "tile00";
		path += std::to_string(i);
		path += ".png";
		temp.loadFromFile(path);
		explosionTextures.push_back(temp);
	}

}

void explosion::animateExplosion(sf::Sprite& targetSprite) {
	sf::Clock clock;
	int i = 0;
	while (i < 8) {
		if (clock.getElapsedTime().asSeconds() > 1.0f) {
			targetSprite.setTexture(explosionTextures[i++]);
			clock.restart();
		}
	}

}