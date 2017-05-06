#pragma once
#include <cmath>
#include <cstdio>
#include <vector>

namespace genomeGlobals
{
	static const float epsilon = 0.000001f;
}


class Genome
{
public:

	bool operator() (const Genome& lhs, const Genome& rhs) const
	{
		return (lhs.fitness < rhs.fitness);
	}

	Genome();
	Genome(int x, int y, int a, int b);
	
	static const int CheckFitness(Genome toCheck);
	static const void PrintGenome(Genome toPrint);
	static const Genome MutateOnePlusOne(const Genome& parent);
	static const Genome Merge(std::vector<Genome> parents);
	static const Genome Combine(std::vector<Genome> parents);

	int genome[4];
	int fitness;
private:

};							