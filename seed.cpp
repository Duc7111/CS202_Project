#include "seed.h"

SEED::SEED() : seed(10, base) {}

SEED::SEED(const std::vector<SEED_T>& seed) : seed(seed) {}

SEED_T& SEED::operator[](size_t idx) {
	return seed[idx];
}

const SEED_T& SEED::operator[](size_t idx) const {
	return seed[idx];
}