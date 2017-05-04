#pragma once
#include <cmath>
#include <cstdio>

namespace genomeGlobals
{
	static const float epsilon = 0.000001f;
}


class Genome
{
public:
	Genome(float x, float y, float a, float b);

	static const float CheckFitness(Genome toCheck);
	static const void PrintFitness(Genome toPrint);

	float genome[4];
private:

};							