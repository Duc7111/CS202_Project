#pragma once
#include <SFML/Graphics.hpp>
class ROAD {
protected:
	sf::Sprite sprite;
	sf::Texture texture;

public:
	ROAD();
	void loadTexture(float y);
	void drawRoad(sf::RenderWindow& window);
};

class GRASS : public ROAD {
public:
	void loadTexture(float y); //overload cai cua thang Grass
};

