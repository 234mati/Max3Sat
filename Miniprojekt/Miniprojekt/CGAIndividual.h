#pragma once
#include "CMax3SatProblem.h"




class CGAIndividual
{
public:
	CGAIndividual(int newTableLen, string problemFileName);
	CGAIndividual();
	~CGAIndividual();
	void SetRandomValues();
	void SetTableLength(int length);
	void LoadProblem(string newFileName);
	CGAIndividual** CrossoverTable(CGAIndividual* other, double crossoverProbability);
	CGAIndividual* Crossover(CGAIndividual* other, double crossoverProbability);
	void Mutation(double mutationProbability);
	int Fitness();
	void PrintTable();
	void PrintProblem();
	CGAIndividual* Copy(CGAIndividual& other);
	CGAIndividual* Copy(CGAIndividual* other);


private: 
	int* table;
	int tableLen;
	CMax3SatProblem* problem;
	string fileName;
};

