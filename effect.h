#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

const std::string explosionPath = "explosion/";
extern std::vector<sf::Texture> explosionTextures;

namespace explosion {
	void loadTexture();

	void explosion::animateExplosion(sf::RenderWindow& window, sf::Sprite& targetSprite); //lam hieu ung no, lam bien mat targetSprite
	//cai nay se dung trong cai gameLose
}

