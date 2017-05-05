#include "Population.h"
#include <map>
#include <functional>
#include <set>
#include "StaticXORShift.h"
#include <algorithm>

Population::Population(int numberOfGenomes)
{

	for (size_t i = 0u; i < numberOfGenomes; ++i)
	{
		Genome newGenome(StaticXorShift::GetIntInRange(-500, 500), StaticXorShift::GetIntInRange(-500, 500), StaticXorShift::GetIntInRange(-500, 500), StaticXorShift::GetIntInRange(-500, 500));
		population.insert(std::pair<int, Genome>(newGenome.fitness, newGenome));
	}
}

void Population::EvolveOnePlusOne()
{
	std::multimap<int, Genome> newPop;

	for (auto it = population.begin(); it != population.end(); ++it) 
	{	
		const Genome& parent = it->second;

		//1+1
		Genome child = Genome::MutateOnePlusOne(parent);

		if (child.fitness < parent.fitness)
		{
			newPop.insert(std::pair<int, Genome>(child.fitness, child));
		} else
		{
			newPop.insert(std::pair<int, Genome>(parent.fitness, parent));
		}
	}

	population = newPop;
}

void Population::EvolveMuPlusLambda(unsigned l)
{
	std::multiset<int, Genome> newPop;

	for(size_t i = 0; i < l; ++i)
	{
		int randVal = StaticXorShift::GetIntInRange(0, population.size()-1);

		const Genome& parent = ;

		Genome child = Genome::MutateOnePlusOne(parent);
	}

	population = newPop;
}

void Population::Print()
{
	printf("\n\r### Printing Population ###\n\r");
	for (auto it = population.begin(); it != population.end(); ++it)
	{
		Genome::PrintGenome(it->second);
		printf("%d\n\r", it->second.fitness);
	}
}

void Population::PrintBestFitness()
{
	printf("\n\r### Printing Best Fitness ###\n\r");
	printf("%d\n\r", population.begin()->second.fitness);
}

bool Population::HasFoundSolution()
{
	return population.begin()->second.fitness == 0;
}


Genome Population::GetBestGenome()
{
	return population.begin()->second;
}
