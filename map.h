#pragma once
#include <vector>
#include "people.h"

class CMAP {
public:
	CMAP();
	void updatePlayerPosition(const CPEOPLE& player);
private:
	static constexpr int width = 31; // intentionally odd
	static constexpr int height = 18;
	static constexpr int cell_size = 40;
	std::vector<std::vector<int>> location; // cell-based location
};