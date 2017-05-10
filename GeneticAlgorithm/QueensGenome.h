#pragma once
#include "Genome.h"
#include "SFML/Graphics.hpp"

class QueensGenome : public Genome
{
public:

	QueensGenome(int numberOfQueens);
	QueensGenome(const QueensGenome& old);
	~QueensGenome();

	bool operator()(const Genome* lhs, const Genome* rhs) const override 
	{
		return (lhs->fitness < rhs->fitness);
	}

	const int CheckFitness() override;
	const void PrintGenome() override;
	Genome* MutateOnePlusOne() const override;
	Genome* Merge(std::vector<Genome*>& parents) const override;
	Genome* Combine(std::vector<Genome*>& parents) const override;
	void PrintPicture();

	int *genome;
	int queenCount;

private:
	QueensGenome();

	Genome* OnePointCrossover(std::vector<Genome*>& parents) const;
	Genome* NPointCrossover(std::vector<Genome*>& parents) const;

};