#include "menu.h"
#include <stdio.h>
#include <string>
#include "settings.h"
#include "game.h"
#include "highScore.h"

sf::Texture menuBg;

void graphicalMenu(sf::RenderWindow& window) {
	menuBg.loadFromFile("menu bg.png");


	sf::Sprite bg(menuBg);
	bg.setScale(1.f, 1.f);


	sf::Font font;
	font.loadFromFile("ZenDots-Regular.ttf");

	sf::Text title;
	title.setFont(font);
	title.setString("Crossing Road");
	title.setCharacterSize(75);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);
	title.setPosition(sf::Vector2f(window.getSize().x / 2 - 100, 50 - diffY));

	auto rectangle = sf::RectangleShape{ {title.getLocalBounds().width + 20,title.getLocalBounds().height + 30} };
	rectangle.setOutlineThickness(5.f);
	rectangle.setPosition(title.getPosition());
	rectangle.setFillColor(sf::Color::Transparent);

	sf::Font font2;
	font2.loadFromFile("SecularOne-Regular.ttf");

	RectangleButton buttons[4];
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
	int index = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			for (auto& button : buttons) {
				button.eventListener(event);
			}
			for (int i = 0; i < 4; i++) {
				if (buttons[i].mousePressed()) {
					index = i;
					switch (index) {
					case 0:
						playGame(window);
						break;
					case 1:
						Settings::settingsSound(window);
						break;
					case 2:
						reloadWindow(window);
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
		}

		window.draw(bg);

		window.draw(rectangle);
		window.draw(title);

		for (auto& button : buttons) {
			button.draw();
		}

		window.display();

	}


}