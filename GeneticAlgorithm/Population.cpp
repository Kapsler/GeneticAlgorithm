#include "Population.h"

Population::Population(int numberOfGenomes)
{
	population.reserve(numberOfGenomes);

	for (size_t i = 0u; i < numberOfGenomes; ++i)
	{
		population.push_back(Genome(gesus.GetIntInRange(-50, 50), gesus.GetIntInRange(-50, 50), gesus.GetIntInRange(-50, 50), gesus.GetIntInRange(-50, 50)));
	}
}

void Population::Evolve()
{
	for (Genome g : population) 
	{
		g.PrintGenome(g);
		printf("%d\n\r", Genome::CheckFitness(g));
		printf("\n\r");
	}
}

void Population::Mutate()
{

}

