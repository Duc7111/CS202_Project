#pragma once
#include <vector>
#include "dice.h"

enum SEED_T : unsigned char {
	base, vehicle, animal 
};

class SEED {
public:
	SEED();
	SEED(const std::vector<SEED_T>& seed);
	SEED_T& operator[](size_t idx);
	const SEED_T& operator[](size_t idx) const;
	void generate();
private:
	static const int boundLower = 3;
	static const int boundUpper = 5;
	std::vector<SEED_T> seed;
};