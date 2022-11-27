#pragma once
#include <SFML/Graphics.hpp>
class Collider
{
public:
	Collider(sf::RectangleShape& obj);

	bool isCollided(Collider& other);

	sf::Vector2f getObjPos();
	sf::Vector2f getObjSize();

private:
	sf::RectangleShape& obj;
};

