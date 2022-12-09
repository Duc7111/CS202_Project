#include "seed.h"

SEED::SEED() {
	generate(current);
	generate(next);
}

SEED::SEED(const std::vector<SEED_T>& seed) {
	std::copy(seed.begin(), seed.begin() + 7, current.begin());
	generate(next);
}

const SEED_T& SEED::operator[](size_t idx) const {
	return current[idx % 7];
}

void SEED::update() {
	std::swap(current, next);
	generate(next);
}

void SEED::generate(std::array<SEED_T, 7>& seed) {
	seed.fill(base);
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

std::string SEED::to_string() {
	std::string str;
	for (const SEED_T& it : current) {
		str += (it == base) ? "0" : ((it == vehicle) ? "1" : "2");
	}
	return str;
}
