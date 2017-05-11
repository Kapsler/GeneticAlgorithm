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
	printf("Genome: (<");
		
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
	if(parents.size() <= 2)
	{
		return OnePointCrossover(parents);
	} 

	return NPointCrossover(parents);
	
}

void QueensGenome::PrintPicture()
{
	sf::Vector2f picSize(1000, 1000);

	sf::RectangleShape square;
	square.setSize(picSize / static_cast<float>(queenCount));
	square.setFillColor(sf::Color::Black);
	square.setPosition(0, 0);

	sf::CircleShape queen;
	queen.setRadius(square.getSize().x / 2.0f);
	queen.setFillColor(sf::Color::Red);
	square.setPosition(0, 0);

	sf::RenderTexture output;
	output.create(1000, 1000);
	output.clear(); 

	for (size_t x = 0; x < queenCount; ++x)
	{
		for (size_t y = 0; y < queenCount; ++y)
		{
			square.setPosition(x * square.getSize().x, y * square.getSize().y);
			queen.setPosition(x * square.getSize().x, y * square.getSize().y);

			if (square.getFillColor() == sf::Color::White)
			{
				square.setFillColor(sf::Color::Black);
			}
			else
			{
				square.setFillColor(sf::Color::White);
			}

			output.draw(square);

			if(genome[x] == y)
			{
				output.draw(queen);
			}
		}

		if (square.getFillColor() == sf::Color::White)
		{
			square.setFillColor(sf::Color::Black);
		}
		else
		{
			square.setFillColor(sf::Color::White);
		}

	}
	output.display();

	sf::Image imageToFile = output.getTexture().copyToImage();
	imageToFile.saveToFile("./output.png");
}

Genome* QueensGenome::OnePointCrossover(std::vector<Genome*>& parents) const
{
	QueensGenome* child = new QueensGenome(*this);

	int randVal = StaticXorShift::GetIntInRange(0, queenCount - 1);

	//One Point Crossover (First and Last Parent from List)
	for (size_t i = 0; i < queenCount; ++i)
	{
		QueensGenome* temp;

		if (i <= randVal)
		{
			temp = static_cast<QueensGenome*>(parents[0]);
		}
		else
		{
			temp = static_cast<QueensGenome*>(parents[parents.size() - 1]);
		}

		child->genome[i] = temp->genome[i];
	}
	child->fitness = child->CheckFitness();

	return child;
}

Genome* QueensGenome::NPointCrossover(std::vector<Genome*>& parents) const
{
	QueensGenome* child = new QueensGenome(*this);


	//N Point Crossover, dependant on parentcount
	int GensPerParent = (queenCount / parents.size()) + 1;


	for (size_t i = 0; i < queenCount; ++i)
	{
		int parentIndex = i / GensPerParent;

		QueensGenome* temp = static_cast<QueensGenome*>(parents[parentIndex]);
		child->genome[i] = temp->genome[i];
	}

	child->fitness = child->CheckFitness();

	return child;
}
