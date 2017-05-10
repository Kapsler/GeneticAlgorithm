#include <cstdio>
#include "Population.h"
#include "StaticXORShift.h"
#include "QueensGenome.h"

namespace config
{
	static const unsigned int MaxGenerations = 10000000;
	static const unsigned int ParentCount = 1000;
	static const unsigned int ChildCount = ParentCount * 2;
}

unsigned long WarumUpRNG()
{
	int result = 0;

	for(int i = 0; i < 1000000; ++i)
	{
		result = StaticXorShift::GetNumber();
	}

	return result;
}

void main()
{
	printf("Warumup: %u\n\r", WarumUpRNG());

	size_t neededIterations = 0;
	std::vector<Genome*> population;
	population.reserve(config::ParentCount);
	for (size_t i = 0u; i < config::ParentCount; ++i)
	{
		population.push_back(new QueensGenome(8));
	}

	Population p(population, Genome());

	p.PrintBestFitness();
	p.GetBestGenome()->PrintGenome();
	
	for(neededIterations; neededIterations < config::MaxGenerations; ++neededIterations)
	{
		if(p.HasFoundSolution())
		{
			break;
		}

		//p.EvolveOnePlusOne();
		//p.EvolveMuPlusLambda(config::ParentCount, config::ChildCount);
		//p.EvolveMuCommaLambda(config::ParentCount, config::ChildCount);
		//p.EvolveMuByPHashLambda(config::ParentCount, config::ChildCount, 2);
		p.GeneticStuff(config::ParentCount, config::ChildCount, 4);
		//p.PrintBestFitness();
		//p.GetBestGenome()->PrintGenome();
	}

	p.PrintBestFitness();
	p.GetBestGenome()->PrintGenome();
	printf("Needed %zd Iterations.\r\n", neededIterations);

}
