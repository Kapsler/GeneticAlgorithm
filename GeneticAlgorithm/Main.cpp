#include <cstdio>
#include "Population.h"
#include "StaticXORShift.h"
#include "QueensGenome.h"
#include "TimerClass.h"
#include "CommandLineParser.h"
#include "SolverGenome.h"

namespace commandLine
{
	enum EvolutionStrategy
	{
		OnePlusOne,
		MuPlusLambda,
		MuCommaLambda,
		MuRhoLambda,
		Genetic
	};

	enum ProblemType
	{
		Solver,
		Queens
	};

	ProblemType type;
	EvolutionStrategy strategy;
	int numberOfQueens = 0;
	int populationSize = 0;
	int parentCount = 0;
	int childCount = 0;
	bool generateImage = false;
	unsigned int maxGenerations = 0;
	unsigned int averageOf = 0;
	bool printPerformance = false;
}

unsigned long WarumUpRNG()
{
	int result = 0;

	for(int i = 0; i < 1000000; ++i)
	{
		result = StaticXorShift::GetNumber();
	}

	return result;
}

bool handleParameters(int argc, char* argv[])
{
	CommandLineParser input(argc, argv);


	if (input.cmdOptionExists("--render"))
	{
		commandLine::generateImage = true;
	} else
	{
		commandLine::generateImage = false;
	}

	if (input.cmdOptionExists("--performance"))
	{
		commandLine::printPerformance = true;
	}
	else
	{
		commandLine::printPerformance = false;
	}

	if (input.cmdOptionExists("--strategy"))
	{
		string param = input.getCmdOption("--strategy");
		if(param == "1+1") {
			commandLine::strategy = commandLine::EvolutionStrategy::OnePlusOne;
		} else if (param == "u+l") {
			commandLine::strategy = commandLine::EvolutionStrategy::MuPlusLambda;
		} else if (param == "u,l") {
			commandLine::strategy = commandLine::EvolutionStrategy::MuCommaLambda;
		} else if (param == "rho") {
			commandLine::strategy = commandLine::EvolutionStrategy::MuRhoLambda;
		} else if (param == "gen") {
			commandLine::strategy = commandLine::EvolutionStrategy::Genetic;
		} else
		{
			cerr << param << " is not a valid input for --strategy" << endl;
			return false;
		}
	} else {
		cerr << "Parameter --strategy not found!" << endl;
		return false;
	}

	if (input.cmdOptionExists("--type"))
	{
		string param = input.getCmdOption("--type");
		if (param == "solver")
		{
			commandLine::type = commandLine::ProblemType::Solver;
		} else if (param == "queens") {
			commandLine::type = commandLine::ProblemType::Queens;

			if(input.cmdOptionExists("--qnum"))
			{
				commandLine::numberOfQueens = stoi(input.getCmdOption("--qnum"));
			} else
			{
				printf("Standard number of Queens is 8. Use --qnum to specify. \n\r");
				commandLine::numberOfQueens = 8;
			}

		} else {
			cerr << param << " is not a valid input for --type" << endl;
			return false;
		}
	}
	else
	{
		cerr << "Parameter --type not found!" << endl;
		return false;
	}

	if (input.cmdOptionExists("--population"))
	{
		commandLine::populationSize = stoi(input.getCmdOption("--population"));
	}
	else
	{
		printf("Standard population size 1000. Use --population to specify. \n\r"); 
		commandLine::populationSize = 1000;
	}

	if (input.cmdOptionExists("--parents"))
	{
		commandLine::parentCount = stoi(input.getCmdOption("--parents"));
	}
	else
	{
		printf("Standard parent size 2. Use --parents to specify. \n\r");
		commandLine::parentCount = 4;
	}

	if (input.cmdOptionExists("--children"))
	{
		commandLine::childCount = stoi(input.getCmdOption("--children"));
	}
	else
	{
		printf("Standard number of children per Generation is 2000. Use --children to specify. \n\r");
		commandLine::childCount = 2000;
	}

	if (input.cmdOptionExists("--generations"))
	{
		commandLine::maxGenerations = stoi(input.getCmdOption("--generations"));
	}
	else
	{
		printf("Standard maximum of Generations is 10000. Use --generations to specify. \n\r");
		commandLine::maxGenerations = 10000;
	}

	if (input.cmdOptionExists("--average"))
	{
		commandLine::averageOf = stoi(input.getCmdOption("--average"));
	}
	else
	{
		commandLine::averageOf = 1;
	}

	return true;
}

Population GeneratePopulation()
{
	std::vector<Genome*> population; 
	population.reserve(commandLine::populationSize);

	if(commandLine::type == commandLine::Queens)
	{
		printf("Generating %d Queen Genomes of size %d.\n\r", commandLine::populationSize, commandLine::numberOfQueens);
		
		for (size_t i = 0u; i < commandLine::populationSize; ++i)
		{
			population.push_back(new QueensGenome(commandLine::numberOfQueens));
		}

	} else if (commandLine::type == commandLine::Solver)
	{
		printf("Generating %d Solver Genomes.\n\r", commandLine::populationSize);

		for (size_t i = 0u; i < commandLine::populationSize; ++i)
		{
			population.push_back(
				new SolverGenome(
					StaticXorShift::GetIntInRange(-500, 500), 
					StaticXorShift::GetIntInRange(-500, 500), 
					StaticXorShift::GetIntInRange(-500, 500), 
					StaticXorShift::GetIntInRange(-500, 500)));
		}
	}

	Population p(population, Genome());

	if (commandLine::averageOf <= 1)
	{
		//Debug Output
		p.PrintBestFitness();
		p.GetBestGenome()->PrintGenome();
	}

	return p;
}

void main(int argc, char* argv[])
{
	if(!handleParameters(argc, argv))
	{
		return;
	}
	printf("Warumup: %u\n\r", WarumUpRNG());

	double averageTime = 0;
	double averageIterations = 0;

	for (size_t a = 0u; a < commandLine::averageOf; ++a)
	{

		size_t neededIterations = 0;
		double neededTime;
		std::vector<int> performanceDataFitness;
		performanceDataFitness.reserve(commandLine::maxGenerations);

		Population p = GeneratePopulation();

		TimerClass timer;
		timer.StartTimer();

		for (neededIterations; neededIterations < commandLine::maxGenerations; ++neededIterations)
		{
			performanceDataFitness.push_back(p.GetBestGenome()->fitness);

			if (p.HasFoundSolution())
			{
				break;
			}

			if (commandLine::strategy == commandLine::EvolutionStrategy::OnePlusOne)
			{
				p.EvolveOnePlusOne();
			}
			else if (commandLine::strategy == commandLine::EvolutionStrategy::MuPlusLambda)
			{
				p.EvolveMuPlusLambda(commandLine::populationSize, commandLine::childCount);
			}
			else if (commandLine::strategy == commandLine::EvolutionStrategy::MuCommaLambda)
			{
				p.EvolveMuCommaLambda(commandLine::populationSize, commandLine::childCount);
			}
			else if (commandLine::strategy == commandLine::EvolutionStrategy::MuRhoLambda)
			{
				p.EvolveMuByPHashLambda(commandLine::populationSize, commandLine::childCount, commandLine::parentCount);
			}
			else if (commandLine::strategy == commandLine::EvolutionStrategy::Genetic)
			{
				p.GeneticStuff(commandLine::populationSize, commandLine::childCount, commandLine::parentCount);
				//p.GeneticStuffMP(commandLine::populationSize, commandLine::childCount, commandLine::parentCount);
			}

			//DebugOutput
			//p.PrintBestFitness();
			//p.GetBestGenome()->PrintGenome();
		}

		neededTime = timer.GetTime(); 

		if(commandLine::averageOf <= 1)
		{
			p.PrintBestFitness();
			p.GetBestGenome()->PrintGenome();
			printf("\n\rNeeded %zd Iterations.\r\n", neededIterations);
			printf("Needed Seconds: %f\n\r", neededTime);
		}
		

		if (commandLine::generateImage && commandLine::type == commandLine::ProblemType::Queens)
		{
			printf("Generating Image...\n\r");
			static_cast<QueensGenome*>(p.GetBestGenome())->PrintPicture();
		}

		averageTime += neededTime;
		averageIterations += neededIterations; 

		//Print Performance Data
		//Fitness
		printf("Performance Fitness:\n\r");
		for (size_t i = 0u; i < performanceDataFitness.size(); ++i)
		{
			printf("%d;", performanceDataFitness[i]);
		}
		printf("\n\r");
	}

	if(commandLine::averageOf > 1)
	{
		averageTime = averageTime / static_cast<double>(commandLine::averageOf);
		averageIterations = averageIterations / static_cast<double>(commandLine::averageOf);
		printf("\n\rAverage of %d Iterations.\n\r", commandLine::averageOf);
		printf("Iterations: %f\n\r", averageIterations);
		printf("Time: %f\n\r", averageTime);
	}


	
}
