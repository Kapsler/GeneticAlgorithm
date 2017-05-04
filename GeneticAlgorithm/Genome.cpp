#include "Genome.h"

Genome::Genome(float x, float y, float a, float b)
{
	genome[0] = x;
	genome[1] = y;
	genome[2] = a;
	genome[3] = b;
}

const float Genome::CheckFitness(Genome toCheck)
{
	float x = toCheck.genome[0];
	float y = toCheck.genome[1];
	float a = toCheck.genome[2];
	float b = toCheck.genome[3];

	//Is mandatory
	if(b >= a)
	{
		return 1000;
	}
	
	float result = abs(((3 * pow(x, 2)) + (5 * pow(y, 3))) - 7 * a + 3 * pow(b, 2));

	if (result < genomeGlobals::epsilon)
	{
		return 0;
	}

	return 1.0f * result;
}

const void Genome::PrintFitness(Genome toPrint)
{
	printf("(<%f,%f,%f,%f>)", toPrint.genome[0], toPrint.genome[1], toPrint.genome[2], toPrint.genome[3]);
}
