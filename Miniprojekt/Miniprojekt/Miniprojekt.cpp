// Miniprojekt.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "CMax3SatProblem.h"
#include "CGAOptimizer.h"
#include <random>

using namespace std;


int main()
{

    
    CGAOptimizer* cga = new CGAOptimizer(40, 0.3 ,0.3, "m3s_50_0.txt",50);
    cga->Initialize();
    cga->PrintProblem();
    cga->PrintPopulation();

    cout<<"Best result: "<<cga->GetBestResult()<<endl;
    for (int i = 0;i < 40;i++) {
        cga->RunIteration();
    }

    cga->PrintPopulation();
    cout << "Best result: " << cga->GetBestResult();
    delete cga;


}
