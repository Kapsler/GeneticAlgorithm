#include "Genome.h"

Genome::Genome(int x, int y, int a, int b)
{
	genome[0] = x;
	genome[1] = y;
	genome[2] = a;
	genome[3] = b;
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
