#pragma once
#include <string>
#include <vector>

using namespace std;

class CMax3SatProblem
{
public:
	CMax3SatProblem() {};
	~CMax3SatProblem();
	void Load(string fileName);
	int Compute(int* values) ;
	int GetSingleValue(int i, int numberInClause, int* values);
	void Printtable();



private:
	vector<string*> clauses;
};

