#pragma once
#include <chrono>

namespace StaticXorShift {

	static unsigned long x = static_cast<unsigned long>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	static unsigned long y = 0xC0FFEE;
	static unsigned long z = 0xDEADBEEF;
	static unsigned long t = 0;

	static unsigned long GetNumber()
	{
		x ^= x << 16;
		x ^= x >> 5;
		x ^= x << 1;

		t = x;
		x = y;
		y = z;
		z = t ^ x ^ y;

		return z;
	}

	static int GetIntInRange(int min, int max)
	{
		return min + (GetNumber() % static_cast<int>(max - min + 1));
	}


};
