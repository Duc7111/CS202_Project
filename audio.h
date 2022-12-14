#include <SFML/Audio.hpp>
#include "settings.h"

const std::string soundFolder = "sound/";
extern sf::Sound lose;
extern sf::Sound move;
extern sf::SoundBuffer sb1;
extern sf::SoundBuffer sb2;

namespace audio {
	void loadSound();

	void playLose();
	void playMove();
}