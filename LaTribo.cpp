#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "GenericTree.h"

using namespace std;

int main()
{
    GenericTree* genericTree = new GenericTree();

    ifstream arq;

    arq.open("./input.txt", ios::in);

    string entrada;

    string pai;
    string filho;
    string terras;

	arq >> terras;

    arq >> pai;

    genericTree->add(pai, stoi(terras), "");

    arq >> filho;
    arq >> terras;

    genericTree->add(filho, stoi(terras), pai);

    while(!arq.eof())
    {
        int attr = 0;

        arq >> pai;
        arq >> filho;
        arq >> terras;

        genericTree->add(filho, stoi(terras), pai);
    }

    genericTree->distribuirTerras();

    genericTree->printPessoaMaisTerras();
}
