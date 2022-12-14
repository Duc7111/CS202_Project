#pragma once
#include "vehicle.h"
#include <SFML/Graphics.hpp>
#include <vector>


bool PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b,
	const sf::Image& imgA, const sf::Image& imgB);
