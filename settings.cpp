#include "settings.h"
#include "menu.h"


sf::Texture muteTex, unmuteTex;


bool Settings::isMuted = false;

void loadTextureOfSettings() {
	muteTex.loadFromFile("mute.png");
	unmuteTex.loadFromFile("unmute.png");
}

void Settings::settingsSound(sf::RenderWindow& window) {

	sf::Font font;
	font.loadFromFile("ZenDots-Regular.ttf");
	sf::Text title;
	title.setFont(font);
	title.setString("Settings");
	title.setCharacterSize(65);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);
	title.setPosition(450, 50);

	sf::Text note(title);
	note.setString("Press Enter to Mute / Unmute.");
	note.setCharacterSize(35);
	note.setPosition(300, 350);


	sf::Sprite sound;
	if (isMuted) {
		sound.setTexture(muteTex);
	}
	else {
		sound.setTexture(unmuteTex);
	}
	sound.setScale(0.5f, 0.5f);
	sound.setPosition(550, 200);


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				graphicalMenu(window);
			}
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::Key::Enter) {
					if (!isMuted) {
						sound.setTexture(muteTex, true);
						isMuted = true;
					}
					else {
						sound.setTexture(unmuteTex, true);
						isMuted = false;
					}
				}
			}
		}

		window.clear();

		window.draw(note);
		window.draw(title);

		window.draw(sound);

		window.display();
	}
}
