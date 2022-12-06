#include "seed.h"

SEED::SEED() : seed(7, base) {}

SEED::SEED(const std::vector<SEED_T>& seed) : seed(seed) {}

SEED_T& SEED::operator[](size_t idx) {
	return seed[idx];
}

const SEED_T& SEED::operator[](size_t idx) const {
	return seed[idx];
}

void SEED::generate() {
	int numRoad = DICE::random(boundLower, boundUpper);
	int road;
	while (numRoad != 0) {
		do {
			road = DICE::random(0, 6);
		} while (seed[road] != base);
		seed[road] = DICE::flip() ? vehicle : animal;
		--numRoad;
	}
}
