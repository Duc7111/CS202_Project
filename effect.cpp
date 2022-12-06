#include "effect.h"
#include<windows.h>
std::vector<sf::Texture> explosionTextures;

void explosion::loadTexture() {
	for (int i = 1; i <= 4; i++) { //co may cai texture no se kh xai hien tai
		sf::Texture temp;
		std::string path = explosionPath + "tile00";
		path += std::to_string(i);
		path += ".png";
		temp.loadFromFile(path);
		explosionTextures.push_back(temp);
	}

}

void explosion::animateExplosion(sf::RenderWindow& window, sf::Sprite& targetSprite) {
	sf::Clock clock;
	int i = 0;
	while (i < explosionTextures.size()) {
		if (clock.getElapsedTime().asSeconds() > explosionBreak) {
			/*window.clear();*/
			targetSprite.setTexture(explosionTextures[i++]);
			targetSprite.setScale(3, 3);
			window.draw(targetSprite);
			window.display();
			clock.restart();
		}
	}

}