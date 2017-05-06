#include <cstdio>
#include "Population.h"
#include "StaticXORShift.h"
#include <bitset>

namespace config
{
	static const unsigned int MaxGenerations = 1000;
	static const unsigned int ParentCount = 1000;
	static const unsigned int ChildCount = ParentCount * 2;
}

void main()
{
	size_t neededIterations = 0;
	std::vector<Genome*> population;
	population.reserve(config::ParentCount);
	for (size_t i = 0u; i < config::ParentCount; ++i)
	{
		population.push_back(
			new SolverGenome(
				StaticXorShift::GetIntInRange(-500, 500), 
				StaticXorShift::GetIntInRange(-500, 500), 
				StaticXorShift::GetIntInRange(-500, 500), 
				StaticXorShift::GetIntInRange(-500, 500)
			));
	}
	Population p(population, SolverGenome());

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
		p.EvolveMuByPHashLambda(config::ParentCount, config::ChildCount, 2);
	}

	p.PrintBestFitness();
	p.GetBestGenome()->PrintGenome();
	printf("Needed %zd Iterations.\r\n", neededIterations);

}
