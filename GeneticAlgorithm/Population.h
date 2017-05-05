#pragma once
#include <vector>
#include "Genome.h"
#include <chrono>
#include <map>

namespace PopulationGlobals
{
	static const int MaxPopulation = 2000;
}

class Population
{
public:
	Population(int numberOfGenomes);

	void Evolve();
	void Print();
	void PrintBestFitness();
	bool HasFoundSolution();
	Genome GetBestGenome();

private:

	std::multimap<int, Genome> population;

};
