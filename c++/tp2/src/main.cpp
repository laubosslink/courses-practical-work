#include <iostream>
#include <math.h>

#include "complexe.h"

using namespace std;

int main()
{
	Complexe A(3,2);

	float x = 2.0;

	cout << "Opérations du type complexe A = 3 + 2i # double x = 2.0  : "<< endl;

	cout << "Operateur + : " << endl;
	(x + A).affiche_complexe();
	cout << "Operateur - : " << endl;
	(x - A).affiche_complexe();
	cout << "Operateur * : " << endl;
	(x * A).affiche_complexe();

	/* test de la fonction retournant le complexe ayant le plus grand module */
	Complexe z2(3, 2);

	cout << " Affichage d'un complexe et de son carré : " << endl;
	z2.affiche_complexe();
	(z2*z2).affiche_complexe();

	cout << "Le plus grand module des deux complexes : " << endl;
	Complexe & z1 = plus_grand(z2, (z2 * z2));
	z1.affiche_complexe();

	cout << "Normalisation du complexe : A = 3 + 2i :" << endl;
	Complexe A_prime = normalise(A);
	A_prime.affiche_complexe();
	cout << "Module : " << A_prime.get_module() << endl;

	cout << "Calcul des racines n-ième de l'unité : " << endl;
	int n;
	cout << "Entrez la valeur de n : " << endl;
	cin >> n;

	Complexe* tab = new Complexe[n];
	racine_unite(n, tab);

	cout << "Racines "<< n << "-ième de l'unité : " << endl;

	for(int i=0; i<n; i++)
		tab[i].affiche_complexe();
	/*
	tab = nullptr;

	cout << "2ème méthode pour les racines "<< n << "ième de l'unité : " << endl;
	racineUnite(n,tab);

	for(int i=0; i<n; i++)
		tab[i].affiche_complexe();
	*/

	return 0;
}
