/** 
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin 
 * F-14050 Caen Cedex 
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */ 

/**
 * @author El Himdi Yasmine <yasmine.elhimdi@ecole.ensicaen.fr> 
 * @author Parmentier Laurent <laurent.parmentier@ecole.ensicaen.fr> 
 * @version 1.2 - 23/11/2014
 */

/**
 * @file main.cpp
 * Programme principal
 */
#include <iostream>

#include <matrice.h>
#include <exception.h>

using namespace std;

int main(){
	
	cout << " nombre de ligne : " << endl;
	unsigned int nb_ligne;
	cin >> nb_ligne; 
	
	cout << "nombre de colonne : " << endl;
	unsigned int nb_colonne;
	cin >> nb_colonne;
	
	Matrice a(nb_ligne, nb_colonne);
	
	cin >> a;  // Utilisation de l'operateur >>

	cout << a; // Utilisation de l'operateur <<
	
	Matrice b = a + a;
	
	cout << "Matrice resultat de la somme a + a : " << endl;
	cout << b;
	
	
	cout << "Affichage d'une ligne de la matrice a : "<< endl;
		
	double *tab = a[1];

	for(int i=0; i<a.get_nb_colonne(); i++){
		cout << tab[i] << "\t";
	}
	
	cout << " " << endl;
	
	cout <<"Transposée de la matrice a "<<endl;
	Matrice t = a.transposer();
	cout << t;

	
	cout << "Une sous matrice de la matrice a : " << endl;
	
	Matrice sm = a.sous_matrice(0,0);
	cout << sm;
	
	cout << "Determinant : " << endl;
	try{
		cout << a.determinant() << endl; 
	}catch( ErreurMatriceCarre emc ){  // Gestion des exceptions 
		cout << emc.what() << endl;
	}
	
	cout << "Inverse de la matrice a : " << endl;
	try{
		Matrice inv = a.inverse();
		cout << inv;
	}catch (ErreurMatriceCarre emc){
		cout << emc.what() << endl;
	}catch(ErreurDeterminant ed){
		cout << ed.what() << endl;
	}

	return 0;
}
