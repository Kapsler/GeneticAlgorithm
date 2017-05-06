#include "Genome.h"
#include "StaticXORShift.h"
#include <bitset>

Genome::Genome()
{
	genome[0] = 0;
	genome[1] = 0;
	genome[2] = 0;
	genome[3] = 0;
	fitness = CheckFitness(*this);
}

Genome::Genome(int x, int y, int a, int b)
{
	genome[0] = x;
	genome[1] = y;
	genome[2] = a;
	genome[3] = b;
	fitness = CheckFitness(*this);
}

const int Genome::CheckFitness(Genome toCheck)
{
	int x = toCheck.genome[0];
	int y = toCheck.genome[1];
	int a = toCheck.genome[2];
	int b = toCheck.genome[3];

	//Is mandatory
	if(b >= a)
	{
		return INT_MAX;
	}

	int result = static_cast<int>(abs(3 * pow(x, 2) + 5 * pow(y, 3) - (7 * a + 3 * pow(b, 2))));

	return result;
}

const void Genome::PrintGenome(Genome toPrint)
{
	printf("(<%d,%d,%d,%d>)\n\r", toPrint.genome[0], toPrint.genome[1], toPrint.genome[2], toPrint.genome[3]);
}

const Genome Genome::MutateOnePlusOne(const Genome& parent)
{
	Genome child = Genome(parent.genome[0], parent.genome[1], parent.genome[2], parent.genome[3]);

	child.genome[0] += StaticXorShift::GetIntInRange(-5, 5);
	child.genome[1] += StaticXorShift::GetIntInRange(-5, 5);
	child.genome[2] += StaticXorShift::GetIntInRange(-5, 5);
	child.genome[3] += StaticXorShift::GetIntInRange(-5, 5);
	child.fitness = CheckFitness(child);
	
	return child;
}

const Genome Genome::Merge(std::vector<Genome> parents)
{
	int mergedX = 0;
	int mergedY = 0;
	int mergedA = 0;
	int mergedB = 0;

	for (Genome& p : parents)
	{
		mergedX += p.genome[0];
		mergedY += p.genome[1];
		mergedA += p.genome[2];
		mergedB += p.genome[3];
	}
	Genome child;

	child.genome[0] = static_cast<int>(mergedX) / parents.size();
	child.genome[1] = static_cast<int>(mergedY) / parents.size();
	child.genome[2] = static_cast<int>(mergedA) / parents.size();
	child.genome[3] = static_cast<int>(mergedB) / parents.size();
	child.fitness = CheckFitness(child);

	return child;
}

const Genome Genome::Combine(std::vector<Genome> parents)
{
	Genome child;

	for(size_t i = 0; i < 4; ++i)
	{
		child.genome[i] = parents[i%parents.size()].genome[i];
	}

	return child;
}
