#pragma once
#include "vehicle.h"
#include <SFML/Graphics.hpp>
#include <vector>


bool PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b,
	const sf::Image& imgA, const sf::Image& imgB);

bool CarNearbySensor(int i, std::vector<CVEHICLE*> generatedVehicles);
//nhan biet co xe xung quanh, dung trong den xanh den do