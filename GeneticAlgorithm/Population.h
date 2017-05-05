#pragma once
#include <vector>
#include "Genome.h"
#include "RNGesus.h"
#include <chrono>

namespace PopulationGlobals
{
	static const int MaxPopulation = 2000;
}

class Population
{
public:
	Population(int numberOfGenomes);

	void Evolve();
	void Mutate();

private:

	RNGesus gesus;
	std::vector<Genome> population;

};
