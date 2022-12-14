#pragma once
#include <SFML/Graphics.hpp>
extern sf::Texture muteTex, unmuteTex;
extern sf::Sprite sound;
void loadTextureOfSettings();
namespace Settings {
	extern bool isMuted;

	void settingsSound(sf::RenderWindow& window);
};

