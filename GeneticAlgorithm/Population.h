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

	//(1+1)
	void EvolveOnePlusOne();

	//(mü + lambda)
	void EvolveMuPlusLambda(unsigned int l);



	//Debug Stuff
	void Print();
	void PrintBestFitness();
	bool HasFoundSolution();
	Genome GetBestGenome();

private:

	std::multimap<int, Genome> population;

};
