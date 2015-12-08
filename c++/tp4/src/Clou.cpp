#include <typeinfo>
#include <iostream>

#include <Obstacle.h>
#include <Compteur.h>
#include <Clou.h>

Clou::~Clou()
{
	if(gere_des_gauche)
	{
		delete gauche;
		gauche = nullptr;
	}

	if(gere_des_droit)
	{
		delete droite;
		droite = nullptr;
	}
}

void Clou::recoitPalet()
{
	Obstacle::recoitPalet();
	transmetPalet();
	perdPalet();
}

void Clou::transmetPalet()
{
	if(!paletPresent())
		return;

	if((std::rand()%2) == 0)
		gauche->recoitPalet();
	else
		droite->recoitPalet();
}

void Clou::set_gere_des_droit(bool val)
{
	gere_des_droit = val;
}

void Clou::set_gere_des_gauche(bool val)
{
	gere_des_gauche = val;
}
