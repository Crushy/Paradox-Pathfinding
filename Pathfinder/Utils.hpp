#pragma once

#include "SquareGrid.hpp"
#include <algorithm>

namespace Utils {
	inline float constexpr lerp(float value, float start, float end) noexcept
	{
		return start + (end - start) * value;
	}

	//Clamps from min (inclusive) to max (exclusive)
	inline int constexpr clamp(int val, int min, int max) noexcept
	{
		int ret = std::min(val, max - 1);
		ret = std::max(ret, min);
		return ret;
	}

	//Estimate distance between nodes
	inline int ManhattanDistance(const Grid::GridLocation& a, const Grid::GridLocation& b) noexcept {
		return abs(a.x - b.x) + abs(a.y - b.y);
	}
}