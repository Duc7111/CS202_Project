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
	title.setPosition(sf::Vector2f(window.getSize().x / 2 - 100, 50));

	auto rectangle = sf::RectangleShape{ {title.getLocalBounds().width + 20,title.getLocalBounds().height + 30} };
	rectangle.setOutlineThickness(5.f);
	rectangle.setPosition(title.getPosition());
	rectangle.setFillColor(sf::Color::Transparent);

	sf::Font font2;
	font2.loadFromFile("SecularOne-Regular.ttf");

	sf::Text options[4];
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			options[i].setString("Play game");
			break;
		case 1:
			options[i].setString("Settings");
			break;
		case 2:
			options[i].setString("Reload");
			break;
		case 3:
			options[i].setString("High score");
			break;
		}
		options[i].setFont(font2);
		options[i].setCharacterSize(50);
		options[i].setPosition(150, 150 + i * 100);
	}

	sf::Text arrow(options[0]);
	arrow.setString("-");
	arrow.setFillColor(sf::Color::Yellow);
	arrow.setPosition(50, 150);

	int index = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Key::W:
					if (index == 0)
						index = 3;
					else
						index--;
					break;
				case sf::Keyboard::Key::S:
					if (index == 3)
						index = 0;
					else
						index++;
					break;
				case sf::Keyboard::Key::Enter: {
					switch (index) {
					case 0:
						playGame(window);
						break;
					case 1:
						Settings::settingsSound(window);
						break;
					case 2:
						playGame(window, true);
						break;
					case 3:
						viewHighScore();
						break;
					}
					break;
				}
				default:
					break;
				}

			}
		}

		for (int i = 0; i < 4; i++) {
			options[i].setFillColor(sf::Color::White);
			options[i].setStyle(sf::Text::Regular);
		}
		options[index].setFillColor(sf::Color::Yellow);
		options[index].setStyle(sf::Text::Underlined);
		arrow.setPosition(50, 150 + 100 * index);

		window.draw(bg);

		window.draw(rectangle);
		window.draw(title);

		window.draw(arrow);
		for (sf::Text option : options) {
			window.draw(option);
		}

		window.display();

	}


}