#pragma once
#include <SFML/Graphics.hpp>
class ROAD {
private:
	sf::Sprite sprite;
	sf::Texture texture;

public:
	void loadTexture(float y);
	void drawRoad(sf::RenderWindow& window);
};
