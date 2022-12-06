#pragma once
#include <random>
#include <vector>

enum SEED_T : unsigned char {
	base, vehicle, animal 
};

class SEED {
public:
	SEED();
	SEED(const std::vector<SEED_T>& seed);
	SEED_T& operator[](size_t idx);
	const SEED_T& operator[](size_t idx) const;
private:
	std::vector<SEED_T> seed;
};