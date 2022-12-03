#include "dice.h"

std::random_device DICE::rd;
std::mt19937 DICE::rng{ DICE::rd() };
std::uniform_int_distribution<int> DICE::coin(0, 1);
std::uniform_int_distribution<int> DICE::uid;

int DICE::random(int low, int high) {
	uid = std::uniform_int_distribution<int>(low, high);
	return uid(rng);
}

int DICE::flip() {
	return coin(rng);
}