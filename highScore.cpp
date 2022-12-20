#include <queue>
#include <fstream>
#include <string>
#include "highScore.h"
#include <iterator>
#include <iostream>
#include "menu.h"
#include "game.h"

std::multiset<int> highScores;

void readHighScore() {
	highScores.clear();

	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs)
		return;
	int size;
	ifs.read((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		int temp;
		ifs.read((char*)&temp, sizeof(int));
		highScores.insert(temp);
	}

	ifs.close();
}

void compareHighScore(int currentScore) //so sánh điểm hiện tại với top highScores
{
	std::multiset<int>::iterator it = highScores.begin();


	if (highScores.empty() || currentScore > *(it))
	{
		if (highScores.size() >= 5)
			highScores.erase(it);
		highScores.insert(currentScore);
		writeHighScore();
	}

}
void writeHighScore() {
	std::ofstream ofs;
	ofs.open(fileName, std::ios::binary);
	int size = highScores.size();
	ofs.write((char*)&size, sizeof(int));
	for (int score : highScores)
		ofs.write((char*)&score, sizeof(int));
	ofs.close();
}
void viewHighScore(sf::RenderWindow& window) {
	sf::Sprite bgSprite(CGAME::bgTexture);
	bgSprite.setScale(1300, 1300);
	bgSprite.setPosition(-100, 0 - diffY);

	sf::Font font;
	font.loadFromFile("SecularOne-Regular.ttf");

	std::vector<sf::Text> scores;
	for (int i = 0; i < 5; i++) {
		sf::Text temp;
		temp.setFont(font);
		temp.setCharacterSize(50);
		sf::FloatRect textRect = temp.getLocalBounds();
		temp.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		temp.setPosition(sf::Vector2f(window.getSize().x / 2 - 100, 200 + i * 100));

		scores.push_back(temp);
	}
	std::multiset<int>::reverse_iterator it = highScores.rbegin();
	int i = 1;
	for (it; it != highScores.rend(); it++)
	{
		std::string str = std::to_string(i) + ". " + std::to_string(*it) + " pts\n";
		scores[i - 1].setString(str);
		i++;
	}

	sf::Font font2;
	font2.loadFromFile("RubikGemstones-Regular.ttf");
	sf::Text title;
	title.setFont(font2);
	title.setString("HIGH SCORE");
	title.setPosition(sf::Vector2f(window.getSize().x / 2 - 150, 100));
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(50);
	title.setStyle(sf::Text::Bold);

	sf::Texture roadTexture;
	roadTexture.loadFromFile("road2.png");
	sf::Sprite roadSprite(roadTexture);
	roadSprite.setPosition(0, 80);
	float scale = (float)M_CELL / (roadSprite.getTexture()->getSize().y);
	roadSprite.setScale(sf::Vector2f(scale, scale));


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				graphicalMenu(window);
			}
		}

		window.clear();

		window.draw(bgSprite);

		for (sf::Text score : scores) {
			window.draw(score);
		}

		window.draw(roadSprite);
		window.draw(title);


		window.display();
	}



}