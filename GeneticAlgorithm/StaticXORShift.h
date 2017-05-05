#pragma once
#include <chrono>

namespace StaticXorShift {

	static unsigned long xs = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	static unsigned long ys = 0xC0FFEE;
	static unsigned long zs = 0xDEADBEEF;

	static unsigned long GetNumber()
	{
		xs ^= xs << 16;
		xs ^= xs >> 5;
		xs ^= xs << 1;

		unsigned long ts = xs;
		xs = ys;
		ys = zs;
		zs = ts ^ xs ^ ys;

		return zs;
	}

	static int GetIntInRange(int min, int max)
	{
		return min + (GetNumber() % static_cast<int>(max - min + 1));
	}


};
