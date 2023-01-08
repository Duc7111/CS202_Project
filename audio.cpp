#include "audio.h"
#include <iostream>

sf::Sound move;
sf::Sound lose;
sf::Sound clockTick;

sf::SoundBuffer sb1;
sf::SoundBuffer sb2;
sf::SoundBuffer sb3;

void audio::loadSound() {

	sb1.loadFromFile(soundFolder + "move.wav");
	move.setBuffer(sb1);

	sb2.loadFromFile(soundFolder + "lose.wav");
	lose.setBuffer(sb2);

	sb3.loadFromFile(soundFolder + "clockTicking.wav");
	clockTick.setBuffer(sb3);
}

void audio::playLose() {
	if (!Settings::isMuted)
		lose.play();
}

void audio::playMove() {
	if (!Settings::isMuted)
		move.play();
}

void audio::clockTicking() {
	if (!Settings::isMuted)
		clockTick.play();
}