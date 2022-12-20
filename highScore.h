#include <set>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

const std::string fileName = "highScore.dat";

extern std::multiset<int> highScores;

void readHighScore();
void compareHighScore(int currentScore); //so sánh điểm hiện tại với top highscore
void writeHighScore();
void viewHighScore(sf::RenderWindow& window);