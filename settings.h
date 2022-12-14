#pragma once
#include <SFML/Graphics.hpp>
extern sf::Texture muteTex, unmuteTex;
void loadTextureOfSettings();
namespace Settings {
	extern bool isMuted;

	void settingsSound(sf::RenderWindow& window);
};

