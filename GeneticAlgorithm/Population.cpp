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

		ChooseRandomParents(parents, p);
		
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
	
	for (size_t i = 0; i < l; ++i) 
	{
		//Choose Parents
		std::vector<Genome*> parents;
		parents.reserve(p);

		//Get Parents based on fitness
		ChooseParentsBasedOnFitness(parents, p);

		//Inheritance
		Genome* child = parents[0]->Combine(parents);

		int randVal = StaticXorShift::GetIntInRange(0, 100);
		if (randVal < 60)
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
	newPop.insert(population.begin(), population.end());
	//Delete all parents
	//for (size_t i = 0; i < population.size(); ++i)
	//{
	//	delete population[i];
	//}
	
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

void Population::GeneticStuffMP(unsigned u, unsigned l, unsigned p)
{
	std::multiset<Genome*, Genome> newPop;

	#pragma omp parallel num_threads(8) 
	{
		for (size_t i = 0; i < l; ++i)
		{
			//Choose Parents
			std::vector<Genome*> parents;
			parents.reserve(p);

			//Get Parents based on fitness
			ChooseParentsBasedOnFitness(parents, p);

			//Inheritance
			Genome* child = parents[0]->Combine(parents);

			int randVal = StaticXorShift::GetIntInRange(0, 100);
			if (randVal < 60)
			{
				//Mutate Child
				Genome* toDelete = child;
				child = child->MutateOnePlusOne();
				delete toDelete;
			}

			//Add new Child to Population
			#pragma omp critical
			{
				newPop.insert(child);
			}
		}
	}

	//Add Parents to Population
	newPop.insert(population.begin(), population.end());
	//Delete all parents
	//for (size_t i = 0; i < population.size(); ++i)
	//{
	//	delete population[i];
	//}

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

void Population::ChooseParentsBasedOnFitness(std::vector<Genome*>& parents, int parentCount)
{
	std::vector<Genome*> tmpPop;
	tmpPop.insert(tmpPop.begin(), population.begin(), population.begin() + population.size() / 5);

	for (size_t j = 0u; j < parentCount; ++j)
	{
		//If all parents were chosen, start anew
		if (tmpPop.size() == 0)
		{
			tmpPop.insert(tmpPop.begin(), population.begin(), population.begin() + population.size() / 5);
		}

		int randVal = StaticXorShift::GetIntInRange(0, tmpPop.size() - 1);

		parents.push_back(tmpPop[randVal]);
		tmpPop.erase(tmpPop.begin() + randVal);
	}
}

void Population::ChooseRandomParents(std::vector<Genome*>& parents, int parentCount)
{
	std::vector<Genome*> tmpPop = population;

	for (size_t j = 0u; j < parentCount; ++j)
	{
		//If all parents were chosen, start anew
		if (tmpPop.size() == 0)
		{
			tmpPop = population;
		}

		size_t randVal = StaticXorShift::GetIntInRange(0, tmpPop.size() - 1);
		parents.push_back(tmpPop[randVal]);
		//Erasing
		tmpPop.erase(tmpPop.begin() + randVal);
	}

}
