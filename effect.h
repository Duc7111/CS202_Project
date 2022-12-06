#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

const std::string explosionPath = "explosion/";
const float explosionBreak = 0.2f;
extern sf::Texture explosionTexture;

namespace explosion {
	void loadTexture();

	void animateExplosion(sf::RenderWindow& window, sf::Sprite targetSprite); //lam hieu ung no, lam bien mat targetSprite
	//cai nay se dung trong cai gameLose
}

