#include "QueensGenome.h"
#include "StaticXORShift.h"

QueensGenome::QueensGenome()
{

}

QueensGenome::QueensGenome(int numberOfQueens)
{
	queenCount = numberOfQueens;

	genome = new int[queenCount];

	for (int i = 0; i < queenCount; ++i)
	{
		genome[i] = StaticXorShift::GetIntInRange(0, queenCount - 1);
	}

	fitness = CheckFitness();
}

QueensGenome::QueensGenome(const QueensGenome& old)
{
	queenCount = old.queenCount;
	genome = new int[queenCount];

	for (int i = 0; i < queenCount; ++i)
	{
		genome[i] = old.genome[i];
	}

	fitness = old.fitness;

}

QueensGenome::~QueensGenome()
{
	delete[] genome;
}

const int QueensGenome::CheckFitness()
{
	int hits = 0;

	for(int x = 0; x < queenCount; ++x)
	{
		for(int y = x + 1; y < queenCount; ++y)
		{
			if(genome[x] == genome[y])
			{
				++hits;
			}
			else if(genome[x] == genome[y] + (y - x) && genome[y] + (y - x) < queenCount)
			{
				++hits;
			} 
			else if(genome[x] == genome[y] - (y - x) && genome[y] - (y - x) >= 0)
			{
				++hits;
			}
		}
	}

	return hits;
}

const void QueensGenome::PrintGenome()
{
	printf("(<");
		
	for(int i = 0; i < queenCount-1; ++i)
	{
		printf("%d,", genome[i]);
	}

	printf("%d", genome[queenCount-1]);
	printf(">)\n\r");
}

Genome* QueensGenome::MutateOnePlusOne() const
{
	QueensGenome* child = new QueensGenome(*this);

	for (int i = 0; i < queenCount; ++i)
	{
		int randVal = StaticXorShift::GetIntInRange(0, queenCount);
	
		if(randVal == 0)
		{
			child->genome[i] += StaticXorShift::GetIntInRange(0 - genome[i], ((queenCount - 1) - genome[i]));
		}
		
	}


	child->fitness = child->CheckFitness();

	return child;
}

Genome* QueensGenome::Merge(std::vector<Genome*>& parents) const
{
	//QueensGenome* child = new QueensGenome(*this);

	//for (int i = 0; i < queenCount; ++i)
	//{
	//	int mergedY = 0;

	//	for (Genome* p : parents)
	//	{
	//		QueensGenome* temp = static_cast<QueensGenome*>(p);
	//		mergedY += temp->genome[i];
	//	}

	//	child->genome[i] = mergedY / static_cast<int>(parents.size());
	//}

	//child->fitness = child->CheckFitness();

	//return child;

	return Combine(parents);
}

Genome* QueensGenome::Combine(std::vector<Genome*>& parents) const
{
	QueensGenome* child = new QueensGenome(*this);

	int randVal = StaticXorShift::GetIntInRange(0, queenCount - 1);

	//One Point Crossover (First and Last Parent from List)
	for (size_t i = 0; i < queenCount; ++i)
	{
		QueensGenome* temp;

		if(i <= randVal)
		{
			temp = static_cast<QueensGenome*>(parents[0]);
		} else
		{
			temp = static_cast<QueensGenome*>(parents[parents.size()-1]);
		}
		
		child->genome[i] = temp->genome[i];
	}
	child->fitness = child->CheckFitness();

	return child;
}
