#pragma once
#include <vector>

class Genome
{
public:
	Genome(){};
	virtual ~Genome(){};

	virtual bool operator() (const Genome* lhs, const Genome* rhs) const 
	{
		return (lhs->fitness < rhs->fitness);
	}

	virtual const int CheckFitness() { return 0; }
	virtual const void PrintGenome() { };
	virtual Genome* MutateOnePlusOne() const { return nullptr; }
	virtual Genome* Merge(std::vector<Genome*>& parents) const { return nullptr; };
	virtual Genome* Combine(std::vector<Genome*>& parents) const { return nullptr; };

	int fitness;
};
