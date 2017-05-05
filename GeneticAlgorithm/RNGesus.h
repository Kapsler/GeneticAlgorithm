#pragma once
#include <chrono>

class RNGesus
{
public:
	RNGesus();
	RNGesus(const unsigned long& xseed, const unsigned long& yseed, const unsigned long& zseed);

	unsigned long GetNumber();
	int GetIntInRange(int min, int max);

private:
	unsigned long x, y, z;
	unsigned long t = 0;
};