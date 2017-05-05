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
	Genome(int x, int y, int a, int b);

	static const int CheckFitness(Genome toCheck);
	static const void PrintGenome(Genome toPrint);

	int genome[4];
private:

};							