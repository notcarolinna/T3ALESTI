#include <iostream>

#pragma once

using namespace std;

class Pessoa
{
private:
	string nome;
	int terras;
public:
	Pessoa();

	string getNome();
	int getTerras();

	void setPessoa(string nome, int terras);
};
