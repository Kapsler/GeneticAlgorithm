#pragma once
#include <vector>
#include "SolverGenome.h"
#include <chrono>
#include <map>
#include <set>
#include "Genome.h"
#include <functional>
#include <unordered_map>

namespace PopulationGlobals
{
	static const int MaxPopulation = 2000;
}

class Population
{
public:
	Population(std::vector<Genome*> newPop, std::function<bool(const Genome* lhs, const Genome* rhs)> pred);

	//(1+1)
	void EvolveOnePlusOne();

	//(m�+lambda)
	void EvolveMuPlusLambda(unsigned int u, unsigned int l);

	//(m�,lambda)
	void EvolveMuCommaLambda(unsigned int u, unsigned int l);

	//(m�/p#lambda)
	void EvolveMuByPHashLambda(unsigned int u, unsigned int l, unsigned int p);

	//Genetic Stuff
	void GeneticStuff(unsigned int u, unsigned int l, unsigned int p);


	//Debug Stuff
	void Print();
	void PrintBestFitness();
	bool HasFoundSolution();
	Genome* GetBestGenome();

private:

	std::vector<Genome*> population;
	std::unordered_multimap<Genome*, int> altersheim;

};
