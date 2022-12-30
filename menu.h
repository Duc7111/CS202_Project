#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include "user_interface.h"

void graphicalMenu(sf::RenderWindow& window);

extern sf::Texture menuBg;

extern sf::SoundBuffer menuSb;
extern sf::Sound menuSound;