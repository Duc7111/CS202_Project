#include "settings.h"


sf::Texture muteTex, unmuteTex;
sf::Sprite sound;

bool Settings::isMuted = false;

void loadTextureOfSettings() {
	muteTex.loadFromFile("mute.png");
	unmuteTex.loadFromFile("unmute.png");
}

void Settings::settingsSound(sf::RenderWindow& window) {
	window.clear();
	sf::Text question;
	question.setString("Change sound setting:");
	if (isMuted)
		sound = sf::Sprite(muteTex);
	else
		sound = sf::Sprite(unmuteTex);
	question.setPosition(350, 50);
	sound.setPosition(700, 50);
	window.draw(sound);
	window.draw(question);

	if (sound.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { //neu bam vao button
			isMuted = !isMuted;
			settingsSound(window);
		}
	}
}
