#include <iostream>

#include <Obstacle.h>

void Obstacle::recoitPalet()
{
	palet_present = true;
}

void Obstacle::perdPalet()
{
	palet_present = false;
}

bool Obstacle::paletPresent()
{
	return palet_present;
}

void Obstacle::set_orphelin(bool val)
{
	est_orphelin = val;
}

bool Obstacle::orphelin()
{
	return est_orphelin;
}

Obstacle::~Obstacle(){}
