#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

const std::string explosionPath = "explosion/";
const float explosionBreak = 0.2f;
extern sf::Texture explosionTexture;

extern int timeCount = 0;

namespace explosion {
	void loadTexture();

	void animateExplosion(sf::Clock& clock, sf::RenderWindow& window, sf::Vector2f position);
	void animateExplosion(sf::Clock& clock, sf::RenderWindow& window, sf::Sprite targetSprite); //lam hieu ung no, lam bien mat targetSprite
	//cai nay se dung trong cai gameLose
};

