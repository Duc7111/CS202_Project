#include "effect.h"
#include<windows.h>
#include "game.h"
#include <thread>
#include <chrono>

sf::Texture explosionTexture;

int timeCount = 0;

void explosion::loadTexture() {
	sf::Texture temp;
	std::string path = explosionPath + "tile003.png";
	temp.loadFromFile(path);
	explosionTexture = sf::Texture(temp);
}

void explodeDraw(sf::RenderWindow& window, sf::Vector2f position) {

}

void explosion::animateExplosion(sf::Clock& clock, sf::RenderWindow& window, sf::Sprite targetSprite) {
	sf::Vector2f explodePos = targetSprite.getPosition();

	sf::Sprite explodeSprite(explosionTexture);
	explodeSprite.setScale(3, 3);
	explodeSprite.setPosition(explodePos - sf::Vector2f(0, 100));
	window.draw(explodeSprite);
	while (timeCount <= 500)
	{
		std::cout << timeCount << " ";
		timeCount++;
	}
	//std::cout << clock.getElapsedTime().asSeconds() << "\n";
	CGAME::singleton().gameLose(window);

	//if (clock.getElapsedTime().asSeconds() > 1.f) {
	//	CGAME::singleton().gameLose(window);
	//}

}

void explosion::animateExplosion(sf::Clock& clock, sf::RenderWindow& window, sf::Vector2f position) {
	sf::Sprite explodeSprite(explosionTexture);
	explodeSprite.setScale(3, 3);
	explodeSprite.setPosition(position - sf::Vector2f(0, 100));
	window.draw(explodeSprite);

	while (timeCount <= 500)
	{
		std::cout << timeCount << " ";
		timeCount++;
	}
	//std::cout << clock.getElapsedTime().asSeconds() << "\n";
	CGAME::singleton().gameLose(window);
	////de no chay effect trc khi qua menu gameLose
	//if (clock.getElapsedTime().asSeconds() > 1.f) {
	//	CGAME::singleton().gameLose(window);
	//}

}