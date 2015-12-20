#pragma once
#include <algorithm>

namespace Utils {
	inline float lerp(float value, float start, float end)
	{
		return start + (end - start) * value;
	}

	//Clamps from min (inclusive) to max (exclusive)
	inline int clamp(int val, int min, int max)
	{
		int ret = std::min(val, max - 1);
		ret = std::max(ret, min);
		return ret;
	}
}