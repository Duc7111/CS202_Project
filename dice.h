#pragma once
#include <random>

class DICE {
public:
	static int random(int low, int high);
	static int flip(); // 0 or 1
private:
	static std::random_device rd;
	static std::mt19937 rng;
	static std::uniform_int_distribution<int> coin;
	static std::uniform_int_distribution<int> uid;
};