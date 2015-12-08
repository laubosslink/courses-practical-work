#include <iostream>
#include <math.h>

#include "complexe.h"

using namespace std;


/*Complexe::Complexe()
{
	Complexe::reel = 0;
	Complexe::imaginaire = 0;
}*/

Complexe::Complexe(float reel, float imaginaire)
{
	Complexe::reel =reel;
	Complexe::imaginaire = imaginaire;
}

Complexe::Complexe(const Complexe & c)
{
	reel = c.reel;
	imaginaire = c.imaginaire;
}

Complexe & Complexe::operator=(const Complexe & c)
{
	reel = c.reel;
	imaginaire = c.imaginaire;
	return *this;
}

float Complexe::get_module() const
{
	return sqrtf(reel * reel + imaginaire * imaginaire);
}

float Complexe::get_argument() const
{
	if(reel == 0)
		return M_PI/2;

	return atanf(imaginaire/reel);
}

void Complexe::affiche_complexe()
{
	cout << reel << " + " << imaginaire << ".i" << endl;
}

void Complexe::swap()
{
	float tmp = reel;
	reel = imaginaire;
	imaginaire = tmp;
}


/* 1.2 */
Complexe somme (const Complexe &a, const Complexe &b)
{
	return Complexe(a.get_reel() + b.get_reel(), a.get_imaginaire() + b.get_imaginaire());
}

Complexe difference(const Complexe &a, const Complexe &b)
{
	return Complexe(a.get_reel() - b.get_reel(), a.get_imaginaire() - b.get_imaginaire());
}

Complexe produit(const Complexe &a, const Complexe &b)
{
return Complexe(a.get_reel()*b.get_reel() - a.get_imaginaire()*b.get_imaginaire(), a.get_reel()*b.get_imaginaire() + a.get_imaginaire()*b.get_reel());
}
/*1.3*/

Complexe operator+(const Complexe &a, const Complexe &b)
{
	return somme(a,b);
}

Complexe operator-(const Complexe &a, const Complexe &b)
{
	return difference(a,b);
}

Complexe operator*(const Complexe &a, const Complexe &b)
{
	return produit(a,b);
}

/**
* 1.4 ) Non on ne peut pas faire un deuxieme constructeur qui prend en argument
* un module et un argument, car ils auraient le type Float, or on l'utilise déjà deux fois.
* En revanche on pourrait créer deux type/classes Argument et Module pour pallier ce probleme.
*/

/* 1.5 */

/*
 MEILLEURE METHODE : Passer des valeurs par defaut au constructeur pour que le compilateur comprenne les opérations entre flottant et le type Complexe.
*/

Complexe normalise(Complexe z){

	return Complexe(cos(z.get_argument()),sin(z.get_argument()));
}

Complexe rotation(Complexe & z, float rot){
	return Complexe (z.get_module()*cos(z.get_argument() + rot),z.get_module()*sin(z.get_argument() + rot));
}

Complexe & plus_grand(Complexe z1, Complexe z2){

	if(z1.get_module() > z2.get_module()){
		Complexe & z = z1;
		return z;
	}

	Complexe & z = z2;
	return z;
}

void racine_unite(int n, Complexe tab[]){

	for(int i=0; i<n; i++)
		tab[i] =  Complexe (cos(2*i*M_PI/n), sin(2*i*M_PI/n));
}

void racineUnite(int n, Complexe tab[]){
	for(int i=0; i<n; i++)
		tab[i] = Complexe(cos(2*i*M_PI/n)) + (sin(2*i*M_PI/n))* Complexe(0,1);

}
