#include <stdio.h>

#include "abr.h"

int main(){
	NOEUD a = creer_arbre();

        insertion_element(a, "ca");
        insertion_element(a, "ce");

	affiche_arbre(a, 0);

	return 0;
}
