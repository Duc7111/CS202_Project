#include <queue>
#include <fstream>
#include <string>
#include "highScore.h"
#include <iterator>

std::multiset<int> highScore;

void readHighScore() {
	highScore.clear();

	std::ifstream ifs;
	ifs.open(fileName, std::ios::binary);
	int size;
	ifs.read((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		int temp;
		ifs.read((char*)&temp, sizeof(int));
		highScore.insert(temp);
	}

	ifs.close();
}

void compareHighScore(int currentScore) //so sánh điểm hiện tại với top highscore
{
	std::multiset<int>::iterator it = highScore.begin();
	if (currentScore > *(it))
	{
		if (highScore.size() == 5)
			highScore.erase(it);
		highScore.insert(currentScore);
		writeHighScore();
	}
}
void writeHighScore() {
	std::ofstream ofs;
	ofs.open(fileName, std::ios::binary);
	int size = highScore.size();
	ofs.write((char*)&size, sizeof(int));
	for (int score : highScore)
		ofs.write((char*)&score, sizeof(int));
	ofs.close();
}
void viewHighScore() {

}