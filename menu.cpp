#include "menu.h"
#include <stdio.h>
#include <string>
#include "settings.h"
#include "game.h"
#include "highScore.h"

sf::Texture menuBg;
sf::SoundBuffer menuSb;
sf::Sound menuSound;

void graphicalMenu(sf::RenderWindow& window) {
	if (!menuSb.loadFromFile("bg.wav")) {
		//cout << "Wrong location . File does not existed";
	}
	menuSound.setBuffer(menuSb);
	menuSound.setVolume(40.f);

	//menuBg.loadFromFile("menu bg.png");
	BACKGROUND background;

	CPEOPLE::loadFile();
	CPEOPLE player;
	player.loadTexture();

	sf::Sprite bg(menuBg);
	bg.setScale(1.f, 1.f);
	

	sf::Font font;
	font.loadFromFile("ZenDots-Regular.ttf");

	sf::Text title, characters;
	title.setFont(font);
	title.setString("Crossing Road");
	title.setCharacterSize(75);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);
	title.setPosition(sf::Vector2f(window.getSize().x / 2 - 100, 50));

	auto rectangle = sf::RectangleShape{ {title.getLocalBounds().width + 20,title.getLocalBounds().height + 30} };
	rectangle.setOutlineThickness(5.f);
	rectangle.setPosition(title.getPosition());
	rectangle.setFillColor(sf::Color::Transparent);

	sf::Font font2;
	font2.loadFromFile("SecularOne-Regular.ttf");

	characters.setFont(font2);
	characters.setString("Character");
	characters.setCharacterSize(40);
	characters.setPosition(550, 290);

	RectangleButton buttons[4], arrows[2];
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			buttons[i].text.setString("Play game");
			break;
		case 1:
			buttons[i].text.setString("Settings");
			break;
		case 2:
			buttons[i].text.setString("Reload");
			break;
		case 3:
			buttons[i].text.setString("High score");
			break;
		}
		buttons[i].setWindow(&window);
		buttons[i].text.setFont(font2);
		buttons[i].text.setCharacterSize(50);
		buttons[i].setSize(340, 100);
		buttons[i].setFillColor(sf::Color::Transparent);
		buttons[i].setPosition(100, 150 + i * 100);
		//buttons[i].setPosition(150, 150 + i * 100 - diffY);
	}
	arrows[0].text.setString("-");
	arrows[1].text.setString("+");
	for (int i = 0; i < 2; ++i) {
		arrows[i].setWindow(&window);
		arrows[i].text.setFont(font2);
		arrows[i].text.setCharacterSize(40);
		arrows[i].setSize(80, 80);
		arrows[i].setFillColor(sf::Color::Transparent);
		arrows[i].setPosition(530 + 160 * i, 350);
	}


	if (!Settings::isMuted)
		menuSound.play();

	player.setPosition(610, 350);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			for (auto& button : buttons) {
				button.eventListener(event);
			}
			for (auto& arrow : arrows) {
				arrow.eventListener(event);
			}
		}

		for (int i = 0; i < 4; i++) {
			if (buttons[i].mousePressed()) {
				switch (i) {
				case 0:
					playGame(window);
					break;
				case 1:
					Settings::settingsMenu(window);
					break;
				case 2:
					reloadWindow(window, false);
					break;
				case 3:
					viewHighScore(window);
					break;
				}
				break;
			}
			else if (buttons[i].mouseHover()) buttons[i].setFillColor(sf::Color(255, 255, 255, 50));
			else buttons[i].setFillColor(sf::Color::Transparent);
		}
		for (int i = 0; i < 2; i++) {
			if (arrows[i].mousePressed()) {
				switch (i) {
				case 0:
					player.switchCharacter(CPEOPLE::getCharacterIndex() - 1);
					break;
				case 1:
					player.switchCharacter(CPEOPLE::getCharacterIndex() + 1);
					break;
				}
				break;
			}
			else if (arrows[i].mouseHover()) arrows[i].setFillColor(sf::Color(255, 255, 255, 50));
			else arrows[i].setFillColor(sf::Color::Transparent);
		}

		/*window.draw(bg);*/

		background.draw(window);
		player.draw(window);


		window.draw(rectangle);
		window.draw(title);
		window.draw(characters);

		for (auto& button : buttons) {
			button.draw();
		}

		for (auto& arrow : arrows) {
			arrow.draw();
		}

		CGAME::defaultView = window.getView();
		window.display();

	}


}