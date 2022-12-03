#pragma once
#include <random>
#include <vector>

enum ROAD_T : unsigned char {
	asphalt, dirt, grass
};

class SEED {
public:
	SEED();
	SEED(const std::vector<ROAD_T>& seed);
	ROAD_T& operator[](size_t idx);
	const ROAD_T& operator[](size_t idx) const;
private:
	std::vector<ROAD_T> seed;
};

class DICE_S {
public:
	DICE_S();
	DICE_S(int numRoadMax);
	void setUpperLimit(int numRoadMax);
	SEED generateSeed();
private:
	bool checkAboveBelow(const SEED& seed, int road);
	int numRoadMax;
	static const int numRoadMin = 3;
	static std::random_device rd;
	static std::mt19937 rng;
	static std::uniform_int_distribution<int> coin;
	static std::uniform_int_distribution<int> uid;
};