#include "RNGesus.h"

RNGesus::RNGesus()
{
	x = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	y = 0xC0FFEE;
	z = 0xDEADBEEF;
}

RNGesus::RNGesus(const unsigned long& xseed, const unsigned long& yseed, const unsigned long& zseed)
{
	x = xseed;
	y = yseed;
	z = zseed;
}

unsigned long RNGesus::GetNumber()
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

int RNGesus::GetIntInRange(int min, int max)
{
	return min + (GetNumber() % static_cast<int>(max - min + 1));
}

