#include "CMax3SatProblem.h"
#include <fstream>
#include <iostream>

using namespace std;


CMax3SatProblem::~CMax3SatProblem() {
	for (int i = clauses.size()-1; i >=0 ; i--) {
		delete[] clauses[i];
	}
}


void CMax3SatProblem::Load(string fileName) {

	ifstream file(fileName, ios::in);
	if (file.is_open()) {
		string word;
		int counterGlobal = 0;
		int counterLocal = 0;
		while (file >> word) {
			if (word.at(0) == ')') {
				counterGlobal++;
				counterLocal = 0;
			}
			else if(word.at(0) == '(') {
				clauses.push_back(new string[3]);
			}
			else if (word == "") {
				
			}
			else {	
				clauses[counterGlobal][counterLocal] = word;
				counterLocal++;
			}
		}
		file.close();
	}

};

int CMax3SatProblem::Compute(int* values) {
	int result = 0;
	for (int i = 0; i < clauses.size(); i++) {
		int x = (GetSingleValue(i, 0, values) + GetSingleValue(i, 1, values) + GetSingleValue(i, 2, values));
		if ( x > -3) {
			result++;
		}
	}
	return result;
};

int CMax3SatProblem::GetSingleValue(int i, int numberInClause, int* values) {
	if (clauses[i][numberInClause].at(0) == '-') {
		return (-1) * values[(-1) * stoi(clauses[i][numberInClause])];
	}
	else {
		return values[stoi(clauses[i][numberInClause])];
	}
};

void CMax3SatProblem::Printtable() {
	cout << endl;
	for (int i = 0; i < clauses.size(); i++) {
		cout << clauses[i][0] << " " << clauses[i][1] << " "<<clauses[i][2] <<  endl;
	}
}
;

