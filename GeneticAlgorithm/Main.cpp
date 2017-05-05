#include <cstdio>
#include "Population.h"
#include "StaticXORShift.h"

namespace config
{
	static const unsigned int MaxGenerations = 50000;
}

void main()
{
	size_t neededIterations = 0;
	Population p(1000);

	p.PrintBestFitness();
	Genome::PrintGenome(p.GetBestGenome());
	
	for(neededIterations; neededIterations < config::MaxGenerations; ++neededIterations)
	{
		if(p.HasFoundSolution())
		{
			break;
		}

		p.EvolveOnePlusOne();
	}

	p.PrintBestFitness();
	Genome::PrintGenome(p.GetBestGenome());
	printf("Needed %d Iterations.\r\n", neededIterations);

}
