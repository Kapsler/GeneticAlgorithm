#include "Population.h"
#include <map>
#include <functional>
#include <set>
#include "StaticXORShift.h"
#include <algorithm>

Population::Population(int numberOfGenomes)
{
	population.reserve(numberOfGenomes);

	for (size_t i = 0u; i < numberOfGenomes; ++i)
	{
		Genome newGenome(StaticXorShift::GetIntInRange(-500, 500), StaticXorShift::GetIntInRange(-500, 500), StaticXorShift::GetIntInRange(-500, 500), StaticXorShift::GetIntInRange(-500, 500));
		population.push_back(newGenome);
	}

	std::sort(population.begin(), population.end(), Genome());
}

void Population::EvolveOnePlusOne()
{
	std::multiset<Genome, Genome> newPop;

	for (auto it = population.begin(); it != population.end(); ++it) 
	{	
		const Genome& parent = *it;

		//1+1
		Genome child = Genome::MutateOnePlusOne(parent);

		if (child.fitness < parent.fitness)
		{
			newPop.insert(child);
		} else
		{
			newPop.insert(parent);
		}
	}

	population.clear();
	population.insert(population.begin(), newPop.begin(), newPop.end());
}

void Population::EvolveMuPlusLambda(unsigned int u, unsigned int l)
{
	std::multiset<Genome, Genome> newPop;
	std::vector<Genome> tmpPop = population;

	for(size_t i = 0; i < l; ++i)
	{
		size_t randVal = StaticXorShift::GetIntInRange(0, population.size()-1);

		const Genome& parent = population[randVal];

		Genome child = Genome::MutateOnePlusOne(parent);

		newPop.insert(parent);
		newPop.insert(child);

		//Erasing
		population.erase(population.begin() + randVal);
		if(population.size() == 0)
		{
			population = tmpPop;
		}
	}

	population.clear();
	population.insert(population.begin(), newPop.begin(), newPop.end());

	
	if(u < population.size())
	{
		population.erase(population.begin() + u, population.end());
	}
}

void Population::EvolveMuCommaLambda(unsigned u, unsigned l)
{
	std::multiset<Genome, Genome> newPop;
	std::vector<Genome> tmpPop = population;

	for (size_t i = 0; i < l; ++i)
	{
		//If all parents were chosen, start anew
		if (population.size() == 0)
		{
			population = tmpPop;
		}

		//Choose Parent
		size_t randVal = StaticXorShift::GetIntInRange(0, population.size() - 1);
		const Genome& parent = population[randVal];//Erasing
		population.erase(population.begin() + randVal);

		//Mutate Child
		Genome child = Genome::MutateOnePlusOne(parent);

		//Add to Population
		newPop.insert(child);
	}

	population.clear();
	population.insert(population.begin(), newPop.begin(), newPop.end());
	if (u < population.size())
	{
		population.erase(population.begin() + u, population.end());
	}
}

void Population::EvolveMuByPHashLambda(unsigned u, unsigned l, unsigned p)
{
	std::multiset<Genome, Genome> newPop;
	std::vector<Genome> tmpPop = population;

	for (size_t i = 0; i < l; ++i)
	{
		//If all parents were chosen, start anew
		if (population.size() == 0)
		{
			population = tmpPop;
		}

		//Choose Parents
		std::vector<Genome> parents(p);
		for(size_t j = 0u; j < p ; ++j)
		{
			size_t randVal = StaticXorShift::GetIntInRange(0, population.size() - 1);
			parents.push_back(population[randVal]);
			//Erasing
			population.erase(population.begin() + randVal);
		}
		
		//Inheritance
		size_t randVal = StaticXorShift::GetIntInRange(0, 1); 
		Genome child;
		if(randVal == 0)
		{
			child = Genome::Merge(parents);
		} else
		{
			child = Genome::Combine(parents);
		}

		randVal = StaticXorShift::GetIntInRange(0, 1);
		if (randVal == 0)
		{	
			//Mutate Child
			child = Genome::MutateOnePlusOne(child);
		}
	
		//Add to Population
		newPop.insert(child);
	}

	population.clear();
	population.insert(population.begin(), newPop.begin(), newPop.end());
	if (u < population.size())
	{
		population.erase(population.begin() + u, population.end());
	}
}

void Population::Print()
{
	printf("\n\r### Printing Population ###\n\r");
	for (auto it = population.begin(); it != population.end(); ++it)
	{
		Genome::PrintGenome(*it);
		printf("%d\n\r", it->fitness);
	}
}

void Population::PrintBestFitness()
{
	printf("\n\r### Printing Best Fitness ###\n\r");
	printf("%d\n\r", population.begin()->fitness);
}

bool Population::HasFoundSolution()
{
	return population.begin()->fitness == 0;
}


Genome Population::GetBestGenome()
{
	return *population.begin();
}

