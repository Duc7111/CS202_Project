#include "randomizer.h"

SEED::SEED() : seed(10, grass) {}

SEED::SEED(const std::vector<ROAD_T>& seed) : seed(seed) {}

ROAD_T& SEED::operator[](size_t idx) {
	return seed[idx];
}

const ROAD_T& SEED::operator[](size_t idx) const {
	return seed[idx];
}

std::random_device DICE_S::rd;
std::mt19937 DICE_S::rng{DICE_S::rd()};
std::uniform_int_distribution<int> DICE_S::coin(0, 1);
std::uniform_int_distribution<int> DICE_S::uid;

DICE_S::DICE_S() : numRoadMax(5) {}

DICE_S::DICE_S(int numRoadMax) {
	if (numRoadMax > 5) this->numRoadMax = 5;
	else if (numRoadMax < 3) this->numRoadMax = 3;
	else this->numRoadMax = numRoadMax;
}

void DICE_S::setUpperLimit(int numRoadMax) {
	if (numRoadMax > 5) this->numRoadMax = 5;
	else if (numRoadMax < 3) this->numRoadMax = 3;
	else this->numRoadMax = numRoadMax;
}

SEED DICE_S::generateSeed() {
	uid = std::uniform_int_distribution<int>(numRoadMin, numRoadMax);
	SEED seed;
	int numRoad = uid(rng);
	int typeRoad = 0;
	int road = 0;
	if (numRoad == 5) {
		for (int i = 1; i < 10; i += 2) {
			typeRoad = coin(rng);
			seed[i] = (typeRoad == 0) ? asphalt : dirt;
		}
		return seed;
	}
	uid = std::uniform_int_distribution<int>(1, 9);
	while (numRoad != 0) {
		road = uid(rng);
		while ((seed[road] != grass) || !checkAboveBelow(seed, road)) {
			road = uid(rng);
		}
		typeRoad = coin(rng);
		seed[road] = (typeRoad == 0) ? asphalt : dirt;
		--numRoad;
	}
	return seed;
}

bool DICE_S::checkAboveBelow(const SEED& seed, int road) {
	if ((road == 9) && (seed[road - 1] != grass)) return false;
	if ((seed[road - 1] != grass) || (seed[road + 1] != grass)) return false;
	return true;
}