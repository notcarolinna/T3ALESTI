#include <iostream>
#include "Pessoa.h"

Pessoa::Pessoa()
{
	this->nome = "";
	this->terras = 0;
}

void Pessoa::setPessoa(string nome, int terras)
{
	if (terras > this->terras)
	{
		this->nome = nome;
		this->terras = terras;
	}
}

string Pessoa::getNome()
{
	return nome;
}

int Pessoa::getTerras()
{
	return terras;
}
