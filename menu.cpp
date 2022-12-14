#include "menu.h"
#include <stdio.h>
#include <string>
#include "settings.h"
#include "game.h"
#include "highScore.h"

sf::Texture menuBg;

void graphicalMenu(sf::RenderWindow& window) {
	int index = 0;

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

	sf::Text option1(title);
	option1.setFont(font2);
	option1.setString("Play game");
	option1.setCharacterSize(50);
	option1.setPosition(50, 150);

	sf::Text option2(option1), option3(option1), option4(option1);
	option2.setString("Settings");
	option2.setPosition(50, 250);
	option3.setString("Reload");
	option3.setPosition(50, 350);
	option4.setString("High score");
	option4.setPosition(50, 450);

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

		option1.setFillColor(sf::Color::White);
		option2.setFillColor(sf::Color::White);
		option3.setFillColor(sf::Color::White);
		option4.setFillColor(sf::Color::White);
		switch (index) {
		case 0:
			option1.setFillColor(sf::Color::Yellow);
			break;
		case 1:
			option2.setFillColor(sf::Color::Yellow);
			break;
		case 2:
			option3.setFillColor(sf::Color::Yellow);
			break;
		case 3:
			option4.setFillColor(sf::Color::Yellow);
			break;
		}
		window.draw(bg);

		window.draw(rectangle);
		window.draw(title);

		window.draw(option1);
		window.draw(option2);
		window.draw(option3);
		window.draw(option4);

		window.display();

	}


}