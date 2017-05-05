#include "Genome.h"
#include "StaticXORShift.h"

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
	
	float result = abs(((3 * pow(x, 2)) + (5 * pow(y, 3))) - 7 * a + 3 * pow(b, 2));

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
	child.fitness = Genome::CheckFitness(child);
	
	return child;
}