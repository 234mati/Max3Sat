#include "CGAIndividual.h"
#include <random>
#include <iostream>

using namespace std;


CGAIndividual::CGAIndividual(int newTableLen, string problemFileName) {
	tableLen = newTableLen;
	table = new int[newTableLen];
	problem = new CMax3SatProblem();
	fileName = problemFileName;
	problem->Load(problemFileName);
}

CGAIndividual::CGAIndividual() {
	tableLen = 0;
	table = nullptr;
	problem = new CMax3SatProblem();
}

CGAIndividual::~CGAIndividual() {
	//cout << "Destkruktor CPAIndividual "<<endl;
	if (table != nullptr) {
		delete[] table;
	}
	delete problem;
}

void CGAIndividual::SetRandomValues() {
	for (int i = 0; i < tableLen; i++) {
		if ((double)rand() / (double)RAND_MAX < 0.5) {
			table[i] = 1;
		}
		else {
			table[i] = -1;
		}
	}
}

void CGAIndividual::SetTableLength(int length) {
	if (table != nullptr) {
		delete[] table;
	}
	tableLen = length;
	table = new int[tableLen];
}

void CGAIndividual::LoadProblem(string newFileName) {
	fileName = newFileName;
	problem->Load(newFileName);
}


int CGAIndividual::Fitness() {
	return problem->Compute(table);
}

void CGAIndividual::Mutation(double mutationProbability) {
	int* copy = new int[tableLen];
	for (int i = 0; i < tableLen; i++) {
		if ((double)rand() / (double)RAND_MAX <= mutationProbability) {
			copy[i] = table[i] * (-1);
		}
		else {
			copy[i] = table[i];
		}
	}

	if (problem->Compute(copy) > problem->Compute(table)) {
		delete[] table;
		table = copy;
		copy = nullptr;
	}
	else {
		delete[] copy;
	}
}

CGAIndividual** CGAIndividual::CrossoverTable(CGAIndividual* other, double crossoverProbability) {
	CGAIndividual** children;
	children = new CGAIndividual*[2];
	children[0] = new CGAIndividual(tableLen, fileName);
	children[1] = new CGAIndividual(tableLen, fileName);
	
	if ((double)rand() / (double)RAND_MAX <= crossoverProbability) {
		for (int i = 0; i < tableLen; i++) {
			if ((double)rand() / (double)RAND_MAX < 0.5) {
				(*children[0]).table[i] = table[i];
				(*children[1]).table[i] = other->table[i];
			}
			else {
				(*children[0]).table[i] = other->table[i];
				(*children[1]).table[i] = table[i];
			}
		}

		if (problem->Compute(children[0]->table) < problem->Compute(table)) {
			delete children[0];
			children[0] = Copy(*this);
			if (problem->Compute(children[1]->table) < problem->Compute(other->table)) {
				delete children[1];
				children[1] = Copy(*other);
			}
		}
		else {
			if (problem->Compute(children[1]->table) < problem->Compute(table)) {
				delete children[1];
				cout << " ";
				children[1] = Copy(*this);

			}
		}
	}
	else {
		delete children[0];
		delete children[1];
		children[0] = Copy(*this);                              
		children[1] = Copy(*other);
	}
	return children;
}

CGAIndividual* CGAIndividual::Crossover(CGAIndividual* other, double crossoverProbability) {
	CGAIndividual* child;
	child = new CGAIndividual(tableLen, fileName);

	if ((double)rand() / (double)RAND_MAX <= crossoverProbability) {
		for (int i = 0; i < tableLen; i++) {
			if ((double)rand() / (double)RAND_MAX < 0.5) {
				(*child).table[i] = table[i];

			}
			else {
				(*child).table[i] = other->table[i];
			}
		}

		if (problem->Compute(child->table) < problem->Compute(table)) {
			delete child;
			child = Copy(*this);
		}
	}
	else {
		delete child;
		child = Copy(*this);                            
	}
	return child;
}

void CGAIndividual::PrintTable() {
	for (int i = 0; i < tableLen; i++) {
		cout <<  " : " << table[i] ;
	}
	cout << endl;
}

void CGAIndividual::PrintProblem() {
	problem->Printtable();
	cout << endl;
}

CGAIndividual* CGAIndividual::Copy(CGAIndividual& other) {
	CGAIndividual* copy = new CGAIndividual(other.tableLen,other.fileName);
	for (int i = 0; i < tableLen; i++) {
		copy->table[i] = other.table[i];
	}
	return copy;
}

CGAIndividual* CGAIndividual::Copy(CGAIndividual* other) {
	CGAIndividual* copy = new CGAIndividual(other->tableLen, other->fileName);
	for (int i = 0; i < tableLen; i++) {
		copy->table[i] = other->table[i];
	}
	return copy;
}