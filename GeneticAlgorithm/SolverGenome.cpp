#include "SolverGenome.h"
#include "StaticXORShift.h"
#include <bitset>

SolverGenome::SolverGenome()
{
	genome[0] = 0;
	genome[1] = 0;
	genome[2] = 0;
	genome[3] = 0;
	fitness = CheckFitness();
}

SolverGenome::SolverGenome(int x, int y, int a, int b)
{
	genome[0] = x;
	genome[1] = y;
	genome[2] = a;
	genome[3] = b;
	fitness = CheckFitness();
}

const int SolverGenome::CheckFitness()
{
	int x = genome[0];
	int y = genome[1];
	int a = genome[2];
	int b = genome[3];

	//Is mandatory
	if (b >= a)
	{
		return INT_MAX;
	}

	int result = static_cast<int>(abs(3 * pow(x, 2) + 5 * pow(y, 3) - (7 * a + 3 * pow(b, 2))));

	return result;
}

const void SolverGenome::PrintGenome()
{
	printf("(<%d,%d,%d,%d>)\n\r", genome[0], genome[1], genome[2], genome[3]);
}

Genome* SolverGenome::MutateOnePlusOne() const
{
	SolverGenome* child = new SolverGenome(genome[0], genome[1], genome[2], genome[3]);

	child->genome[0] += StaticXorShift::GetIntInRange(-5, 5);
	child->genome[1] += StaticXorShift::GetIntInRange(-5, 5);
	child->genome[2] += StaticXorShift::GetIntInRange(-5, 5);
	child->genome[3] += StaticXorShift::GetIntInRange(-5, 5);
	child->fitness = child->CheckFitness();

	return child;
}

Genome* SolverGenome::Merge(std::vector<Genome*>& parents) const
{
	int mergedX = 0;
	int mergedY = 0;
	int mergedA = 0;
	int mergedB = 0;
	
	for (Genome* p : parents)
	{
		SolverGenome* temp = static_cast<SolverGenome*>(p);
		mergedX += temp->genome[0];
		mergedY += temp->genome[1];
		mergedA += temp->genome[2];
		mergedB += temp->genome[3];
	}

	SolverGenome* child = new SolverGenome();

	child->genome[0] = mergedX / (int)parents.size();
	child->genome[1] = mergedY / (int)parents.size();
	child->genome[2] = mergedA / (int)parents.size();
	child->genome[3] = mergedB / (int)parents.size();
	child->fitness = child->CheckFitness();

	return child;
}

Genome* SolverGenome::Combine(std::vector<Genome*>& parents) const
{
	SolverGenome* child = new SolverGenome();

	for(size_t i = 0; i < sizeof(child->genome) / sizeof(int); ++i)
	{
		SolverGenome* temp = static_cast<SolverGenome*>(parents[i%parents.size()]);
		child->genome[i] = temp->genome[i];
	}
	child->fitness = child->CheckFitness();

	return child;
}
