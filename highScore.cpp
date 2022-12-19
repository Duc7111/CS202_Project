#include <queue>
#include <fstream>
#include <string>
#include "highScore.h"
#include <iterator>
#include <iostream>

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
void viewHighScore() {
	std::multiset<int>::reverse_iterator it = highScores.rbegin();
	int i = 1;
	for (it; it != highScores.rend(); it++)
	{
		std::cout << i << " - ";
		std::cout << *it << "\n";
	}

}