#pragma once
#include <vector>
#include "Genome.h"

namespace genomeGlobals
{
	static const float epsilon = 0.000001f;
}

class SolverGenome : public Genome
{
public:

	virtual bool operator() (const Genome* lhs, const Genome* rhs) const override
	{
		return (lhs->fitness < rhs->fitness);
	}

	SolverGenome(int x, int y, int a, int b);
	
	virtual const int CheckFitness() override;
	virtual const void PrintGenome() override;
	virtual Genome* MutateOnePlusOne() const override;
	virtual Genome* Merge(std::vector<Genome*>& parents) const override;
	virtual Genome* Combine(std::vector<Genome*>& parents) const override;

	int genome[4];

private:
	SolverGenome();

};							