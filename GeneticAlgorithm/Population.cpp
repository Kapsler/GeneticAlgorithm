#include "Population.h"
#include "StaticXORShift.h"
#include <functional>
#include <set>
#include <algorithm>

Population::Population(std::vector<Genome*> newPop, std::function<bool(const Genome* lhs, const Genome* rhs)> pred)
{
	population.reserve(newPop.size());
	population.insert(population.begin(), newPop.begin(), newPop.end());
	std::sort(population.begin(), population.end(), pred);
}

void Population::EvolveOnePlusOne()
{
	std::multiset<Genome*, Genome> newPop;

	for (auto it = population.begin(); it != population.end(); ++it) 
	{	
		Genome* parent = *it;

		//1+1
		Genome* child = parent->MutateOnePlusOne();

		if (child->fitness < parent->fitness)
		{
			newPop.insert(child);
			delete parent;
		} else
		{
			newPop.insert(parent);
			delete child;
		}
	}

	population.clear();
	population.insert(population.begin(), newPop.begin(), newPop.end());
}

void Population::EvolveMuPlusLambda(unsigned int u, unsigned int l)
{
	std::multiset<Genome*, Genome> newPop;
	std::vector<Genome*> tmpPop = population;
	
	for(size_t i = 0; i < l; ++i)
	{
		if (population.size() == 0)
		{
			population = tmpPop;
		}

		size_t randVal = StaticXorShift::GetIntInRange(0, population.size()-1);
		Genome* parent = population[randVal];
		//Erasing
		population.erase(population.begin() + randVal);

		Genome* child = parent->MutateOnePlusOne();

		//Add new Child
		newPop.insert(child);
	}
	//Add Parents
	newPop.insert(tmpPop.begin(), tmpPop.end());

	population.clear();
	population.insert(population.begin(), newPop.begin(), newPop.end());
	
	if(u < population.size())
	{
		for(size_t i = u; i < population.size(); ++i)
		{
			delete population[i];
		}
		population.erase(population.begin() + u, population.end());
	}
}

void Population::EvolveMuCommaLambda(unsigned u, unsigned l)
{
	std::multiset<Genome*, Genome> newPop;
	std::vector<Genome*> tmpPop = population;

	for (size_t i = 0; i < l; ++i)
	{
		//If all parents were chosen, start anew
		if (population.size() == 0)
		{
			population = tmpPop;
		}

		//Choose Parent
		size_t randVal = StaticXorShift::GetIntInRange(0, population.size() - 1);
		Genome* parent = population[randVal];
		//Erasing
		population.erase(population.begin() + randVal);

		//Mutate Child
		Genome* child = parent->MutateOnePlusOne();

		//Add new Child to Population
		newPop.insert(child);
	}

	for (size_t i = 0; i < tmpPop.size(); ++i)
	{
		delete tmpPop[i];
	}

	population.clear();
	population.insert(population.begin(), newPop.begin(), newPop.end());
	if (u < population.size())
	{
		 for(size_t i = u; i < population.size(); ++i)
		 {
			delete population[i];
		 }
		population.erase(population.begin() + u, population.end());
	}
}

void Population::EvolveMuByPHashLambda(unsigned u, unsigned l, unsigned p)
{
	std::multiset<Genome*, Genome> newPop;
	std::vector<Genome*> tmpPop = population;

	for (size_t i = 0; i < l; ++i)
	{
		//Choose Parents
		std::vector<Genome*> parents;
		parents.reserve(p);
		for(size_t j = 0u; j < p; ++j)
		{
			//If all parents were chosen, start anew
			if (population.size() == 0)
			{
				population = tmpPop;
			}

			size_t randVal = StaticXorShift::GetIntInRange(0, population.size() - 1);
			parents.push_back(population[randVal]);
			//Erasing
			population.erase(population.begin() + randVal);
		}
		
		//Inheritance
		size_t randVal = StaticXorShift::GetIntInRange(0, 1); 
		Genome* child;
		if (randVal == 0)
		{
			child = parents[0]->Merge(parents);
		} else
		{
			child = parents[0]->Combine(parents);
		}

		randVal = StaticXorShift::GetIntInRange(0, 50);
		if (randVal == 0)
		{	
			//Mutate Child
			Genome* toDelete = child;
			child = child->MutateOnePlusOne();
			delete toDelete;
		}
	
		//Add new Child to Population
		newPop.insert(child);
	}
	//Add Parents to Population
	newPop.insert(tmpPop.begin(), tmpPop.end());

	population.clear();
	population.insert(population.begin(), newPop.begin(), newPop.end());
	if (u < population.size())
	{
		for(size_t i = u; i < population.size(); ++i)
		{
			delete population[i];
		}
		population.erase(population.begin() + u, population.end());
	}
}

void Population::GeneticStuff(unsigned u, unsigned l, unsigned p)
{
	std::multiset<Genome*, Genome> newPop;
	std::vector<Genome*> tmpPop = population;

	
	for (size_t i = 0; i < l; ++i) 
	{
		//Choose Parents
		std::vector<Genome*> parents;
		parents.reserve(p);

		//Get Parents based on fitness
		for (size_t j = 0u; j < p; ++j)
		{
			//If all parents were chosen, start anew
			if (population.size() == 0)
			{
				population = tmpPop;
			}

			for (size_t k = 0; true; ++k)
			{
				if (k >= population.size())
				{
					k = 0;
				}

				float randVal = StaticXorShift::GetZeroToOne();

				Genome* potentialParent = population[k];

				if(1.0f / static_cast<float>(potentialParent->fitness) > randVal)
				{
					parents.push_back(potentialParent);

					//Erasing
					population.erase(population.begin() + k);
					break;
				}
			}
		}

		//Inheritance
		Genome* child = parents[0]->Combine(parents);
		

		int randVal = StaticXorShift::GetIntInRange(0, 10);
		if (randVal == 0)
		{
			//Mutate Child
			Genome* toDelete = child;
			child = child->MutateOnePlusOne();
			delete toDelete;
		}

		//Add new Child to Population
		newPop.insert(child);
	}
	//Add Parents to Population
	//newPop.insert(tmpPop.begin(), tmpPop.end());
	//Delete all parents
	for (size_t i = 0; i < tmpPop.size(); ++i)
	{
		delete tmpPop[i];
	}
	
	population.clear();
	population.insert(population.begin(), newPop.begin(), newPop.end());
	if (u < population.size())
	{
		for (size_t i = u; i < population.size(); ++i)
		{
			delete population[i];
		}
		population.erase(population.begin() + u, population.end());
	}
}


void Population::Print()
{
	printf("\n\r### Printing Population ###\n\r");
	for (auto it = population.begin(); it != population.end(); ++it)
	{
		(*it)->PrintGenome();
		printf("%d\n\r", (*it)->fitness);
	}
}

void Population::PrintBestFitness()
{
	printf("\n\r### Printing Best Fitness ###\n\r");
	printf("%d\n\r", (*population.begin())->fitness);
}

bool Population::HasFoundSolution()
{
	return (*population.begin())->fitness == 0;
}


Genome* Population::GetBestGenome()
{
	return *population.begin();
}

