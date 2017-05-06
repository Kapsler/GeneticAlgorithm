#include <cstdio>
#include "Population.h"
#include "StaticXORShift.h"
#include <bitset>

namespace config
{
	static const unsigned int MaxGenerations = 50000;
	static const unsigned int ParentCount = 1000;
	static const unsigned int ChildCount = ParentCount * 2;
}

void main()
{
	size_t neededIterations = 0;
	Population p(config::ParentCount);

	p.PrintBestFitness();
	Genome::PrintGenome(p.GetBestGenome());
	
	for(neededIterations; neededIterations < config::MaxGenerations; ++neededIterations)
	{
		if(p.HasFoundSolution())
		{
			break;
		}

		//p.EvolveOnePlusOne();
		//p.EvolveMuPlusLambda(config::ParentCount, config::ChildCount);
		//p.EvolveMuCommaLambda(config::ParentCount, config::ChildCount);
		p.EvolveMuByPHashLambda(config::ParentCount, config::ChildCount, 2);
	}

	p.PrintBestFitness();
	Genome::PrintGenome(p.GetBestGenome());
	printf("Needed %d Iterations.\r\n", neededIterations);

}
