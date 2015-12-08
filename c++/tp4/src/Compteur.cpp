#include <iostream>

#include <Compteur.h>

void Compteur::recoitPalet()
{
	Obstacle::recoitPalet();
	compteur++;

	if(suivant != nullptr)
	{
		suivant->recoitPalet();
		perdPalet();
	}
}

int Compteur::getCompteur()
{
	return compteur;
}

Compteur::~Compteur(){}
