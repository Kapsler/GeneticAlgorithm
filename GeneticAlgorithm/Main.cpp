#include <cstdio>
#include "Population.h"
#include "StaticXORShift.h"

void main()
{
	size_t neededIterations = 0;
	Population p(1000);

	p.PrintBestFitness();
	Genome::PrintGenome(p.GetBestGenome());
	
	for(neededIterations; neededIterations < 50000; ++neededIterations)
	{
		if(p.HasFoundSolution())
		{
			break;
		}

		p.Evolve();
	}

	p.PrintBestFitness();
	Genome::PrintGenome(p.GetBestGenome());
	printf("Needed %d Iterations.\r\n", neededIterations);

}
