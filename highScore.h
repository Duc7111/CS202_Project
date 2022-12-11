#include <set>
#include <fstream>
#include <string>

const std::string fileName = "highScore.dat";

extern std::multiset<int> highScore;

void readHighScore();
void compareHighScore(int currentScore); //so sánh điểm hiện tại với top highscore
void writeHighScore();
void viewHighScore();