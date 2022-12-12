#pragma once
#include <string>
#include <array>
#include "dice.h"

enum SEED_T : unsigned char {
	base, vehicle, animal 
};

class SEED {
public:
	SEED();
	SEED(const std::vector<SEED_T>& seed);
	void update();
	const SEED_T& operator[](size_t idx) const;
	std::string to_string();
private:
	static const int boundLower = 3;
	static const int boundUpper = 5;
	static void antiSpawnCamping(std::array<SEED_T, 7>& seed);
	static void generate(std::array<SEED_T, 7>& seed);
	std::array<SEED_T, 7> current;
	std::array<SEED_T, 7> next;
};