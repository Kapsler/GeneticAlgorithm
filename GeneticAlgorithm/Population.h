#pragma once
#include <vector>
#include "Genome.h"
#include <chrono>
#include <map>
#include <set>

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

	//(m�+lambda)
	void EvolveMuPlusLambda(unsigned int u, unsigned int l);

	//(m�,lambda)
	void EvolveMuCommaLambda(unsigned int u, unsigned int l);

	//(m�/p#lambda)
	void EvolveMuByPHashLambda(unsigned int u, unsigned int l, unsigned int p);



	//Debug Stuff
	void Print();
	void PrintBestFitness();
	bool HasFoundSolution();
	Genome GetBestGenome();

private:

	std::vector<Genome> population;

};
