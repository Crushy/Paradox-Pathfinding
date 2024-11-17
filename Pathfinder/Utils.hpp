#pragma once

#include "SquareGrid.h"
#include <algorithm>

namespace utils {
	constexpr float lerp(const float value, const float start, const float end) noexcept
	{
		return start + (end - start) * value;
	}

	//Clamps from min (inclusive) to max (exclusive)
	constexpr int clamp(const int val, const int min, const int max) noexcept
	{
		int ret = std::min(val, max - 1);
		ret = std::max(ret, min);
		return ret;
	}

	//Estimate distance between nodes
	inline float manhattan_distance(const grid::GridLocation& a, const grid::GridLocation& b) noexcept {
		return static_cast<float>(abs(a.x - b.x) + abs(a.y - b.y));
	}
}