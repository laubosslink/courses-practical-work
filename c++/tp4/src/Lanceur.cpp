#include <iostream>

#include <Lanceur.h>
#include <Clou.h>

void Lanceur::lancer()
{

	if(obstacle_depart != nullptr)
		obstacle_depart->recoitPalet();
}

Lanceur::~Lanceur()
{
		delete obstacle_depart;
		obstacle_depart = nullptr;
}
