#include "CGAOptimizer.h"
#include <iostream>


using namespace std;



CGAOptimizer::CGAOptimizer(int newPopulationSize, double newMutationProbability, double newCrossoverProbability, string newFileName, int newCompartment) {
	populationSize = newPopulationSize;
	mutationProbability = newMutationProbability;
	crossoverProbability = newCrossoverProbability;
	fileName = newFileName;
	compartment = newCompartment;
}

CGAOptimizer::~CGAOptimizer() {
	for (int i = population.size() - 1; i >= 0; i--) {
			delete population[i];
	}
}


void CGAOptimizer::SetPopulationSize(double newPopulationSize) {
	if (newPopulationSize < populationSize) {
		for (int i = populationSize-1; i >= newPopulationSize; i--) {
			population.pop_back();
		}
	}
	else if(newPopulationSize > populationSize){

	}
}


void CGAOptimizer::Initialize() {
	for (int i = 0; i < populationSize; i++) {
		population.push_back(new CGAIndividual(compartment, fileName));
		population[i]->SetRandomValues();
		}
}


void CGAOptimizer::RunIteration() {
	vector<CGAIndividual*> newPopulation;
	while (newPopulation.size() < populationSize) {
		int t1 = rand() % populationSize;
		int t2 = rand() % populationSize;
		CGAIndividual* parent1 = Duel(t1,t2);
		t1 = rand() % populationSize;
		t2 = rand() % populationSize;
		CGAIndividual* parent2 = Duel(t1, t2);


		CGAIndividual** children = new CGAIndividual*[2];

		if (parent1->Fitness() > parent2->Fitness()) {
			children[0] = parent1->Crossover(parent2, crossoverProbability);
			children[1] = parent1->Crossover(parent2, crossoverProbability);

		}
		else {
			children[0] = parent2->Crossover(parent1, crossoverProbability);
			children[1] = parent2->Crossover(parent1, crossoverProbability);
		}


		newPopulation.push_back(children[0]);
		newPopulation.push_back(children[1]);

		delete[] children;
		cout << "";
		
	}
	for (int i = 0;i < population.size();i++) {
		delete population[i];
	}
	population.clear();
	for (int i = 0;i < newPopulation.size();i++) {
		population.push_back(newPopulation[i]);
	}
	populationSize = population.size();

}


CGAIndividual* CGAOptimizer::Duel(int n1, int n2) {
	if (population[n1]->Fitness() > population[n2]->Fitness()) {
		return population[n1];
	}
	else {
		return population[n2];
	}
}

CGAIndividual* CGAOptimizer::Duel(CGAIndividual* n1, CGAIndividual* n2) {
	if (n1->Fitness() > n2->Fitness()) {
		return n1;
	}
	else {
		return n2;
	}
}

void CGAOptimizer::PrintPopulation() {
	for (int i = 0; i < populationSize; i++) {
		population[i]->PrintTable();
	}
}
void CGAOptimizer::PrintProblem() {
	population[0]->PrintProblem();
}

int CGAOptimizer::GetBestResult() {
	int result = 0;
	for (int i = 0; i < populationSize; i++) {
		int fitness = population[i]->Fitness();
		cout << " Fitness: " << population[i]->Fitness()<<"  ";
		if (result < fitness) {
			result = fitness;
		}
	}
	return result;
}
