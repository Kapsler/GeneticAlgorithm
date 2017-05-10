#pragma once
#include <vector>
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

	//(mü+lambda)
	void EvolveMuPlusLambda(unsigned int u, unsigned int l);

	//(mü,lambda)
	void EvolveMuCommaLambda(unsigned int u, unsigned int l);

	//(mü/p#lambda)
	void EvolveMuByPHashLambda(unsigned int u, unsigned int l, unsigned int p);

	//Genetic Stuff
	void GeneticStuff(unsigned int u, unsigned int l, unsigned int p);
	void GeneticStuffMP(unsigned int u, unsigned int l, unsigned int p);


	//Debug Stuff
	void Print();
	void PrintBestFitness();
	bool HasFoundSolution();
	Genome* GetBestGenome();

private:

	std::vector<Genome*> population;
	std::unordered_multimap<Genome*, int> altersheim;

	void ChooseParentsBasedOnFitness(std::vector<Genome*>& parents, int parentCount);
	void ChooseRandomParents(std::vector<Genome*>& parents, int parentCount);

};
