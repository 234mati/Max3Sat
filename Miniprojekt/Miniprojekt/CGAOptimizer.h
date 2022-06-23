#pragma once
#include "CGAIndividual.h"
#include <random>
#include <vector>



class CGAOptimizer
{

public:
	
	CGAOptimizer(int newPopulationSize, double newMutationProbability, double newCrossoverProbability, string newFileName,int newCompartment);
	~CGAOptimizer();
	void SetMutationProbability(double newMutationProbability) { mutationProbability = newMutationProbability; }
	void SetCrossoverProbability(double newCrossoverProbability) { crossoverProbability = newCrossoverProbability; }
	void SetPopulationSize(double newPopulationSize);
	void Initialize();
	void RunIteration();
	CGAIndividual* Duel(int n1, int n2);
	CGAIndividual* Duel(CGAIndividual* n1, CGAIndividual* n2);
	void PrintPopulation();
	void PrintProblem();
	int GetBestResult();



private:
	int populationSize;
	double mutationProbability;
	double crossoverProbability;
	vector<CGAIndividual*> population;
	string fileName;
	int compartment;
};

