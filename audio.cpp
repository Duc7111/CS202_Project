#include "audio.h"
#include <iostream>

sf::Sound move;
sf::Sound lose;

sf::SoundBuffer sb1;
sf::SoundBuffer sb2;

void audio::loadSound() {

	sb1.loadFromFile(soundFolder + "move.wav");
	move.setBuffer(sb1);

	sb2.loadFromFile(soundFolder + "lose.wav");
	lose.setBuffer(sb2);
}

void audio::playLose() {
	if (!Settings::isMuted)
		lose.play();
}

void audio::playMove() {
	if (!Settings::isMuted)
		move.play();
}