#include "effect.h"
#include<windows.h>
#include "game.h"
#include <thread>
#include <chrono>

sf::Texture explosionTexture;

void explosion::loadTexture() {
	sf::Texture temp;
	std::string path = explosionPath + "tile003.png";
	temp.loadFromFile(path);
	explosionTexture = sf::Texture(temp);
}

void explosion::animateExplosion(sf::RenderWindow& window, sf::Sprite targetSprite) {
	sf::Vector2f explodePos = targetSprite.getPosition();
	sf::Sprite explodeSprite(explosionTexture);
	explodeSprite.setScale(3, 3);
	explodeSprite.setPosition(explodePos - sf::Vector2f(0, 100));
	window.draw(explodeSprite);

	CGAME::gameLose();
}

void explosion::animateExplosion(sf::RenderWindow& window, sf::Vector2f position) {
	sf::Sprite explodeSprite(explosionTexture);
	explodeSprite.setScale(3, 3);
	explodeSprite.setPosition(position - sf::Vector2f(0, 100));
	window.draw(explodeSprite);

	CGAME::gameLose();
}