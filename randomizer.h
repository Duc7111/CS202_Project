#pragma once
#include <random>
#include <vector>

enum ROAD_T : unsigned char {
	asphalt, dirt, grass
};

class CSEED {
public:
	CSEED();
	CSEED(const std::vector<ROAD_T>& seed);
	ROAD_T& operator[](size_t idx);
	const ROAD_T& operator[](size_t idx) const;
private:
	std::vector<ROAD_T> seed;
};

class DICE {
public:
	DICE();
	DICE(int numRoadMax);
	void setUpperLimit(int numRoadMax);
	CSEED generateSeed();
private:
	bool checkAboveBelow(const CSEED& seed, int road);
	int numRoadMax;
	static const int numRoadMin = 3;
	static std::random_device rd;
	static std::mt19937 rng;
	static std::uniform_int_distribution<int> coin;
	static std::uniform_int_distribution<int> uid;
};