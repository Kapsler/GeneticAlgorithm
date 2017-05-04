#include <cstdio>
#include "Genome.h"

void main()
{
	
	Genome g1(2.0f, -1.0f, 1.0f, 0.0f);
	Genome g2(1.0f, 4.0f, -1.0f, -50.0f);

	float fitness1 = Genome::CheckFitness(g1);
	float fitness2 = Genome::CheckFitness(g2);

	printf("%f\n\r", fitness1);
	printf("%f\n\r", fitness2);
}
