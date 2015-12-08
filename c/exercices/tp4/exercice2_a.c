#include <stdio.h>
#include <stdlib.h>

void lire(int *tab, int taille){
	int i;

	for(i=0; i<taille; i++)
	{
		printf("tab[%d]:", i);
		scanf("%d", tab+i);
	}
}

void afficher(int *tab, int taille){
	int i;

	for(i=0; i<taille; i++)
		printf("tab[%d]=%d\n", i, tab[i]);
}

float calcul_moyen(int *tab, int taille){
	int i;
	float moyenne=0;

	if(taille == 0){
		fprintf(stderr, "La taille ne peut pas etre nulle.");
		return -1;
	}

	for(i=0; i<taille; i++)
		moyenne += tab[i];

	return moyenne/taille;
}

int exercice2_a(void) {
	int *tab, taille=0, choix;

	tab = NULL;

	do {
		printf("Que voulez-vous faire ?\n");
		printf("0: Quitter\n");
		printf("1: Saisir un nouveau tableau\n");
		printf("2: Afficher les elements du tableau\n");
		printf("3: Afficher la moyenne des données du tableau\n");
		printf("Choix: ");
		scanf("%d", &choix);

		if(choix <= 0 || choix > 3)
			break;

		printf("\n");

		if(choix == 1){
			printf("Taille du tableau: ");
			scanf("%d", &taille);

			/* si la taille n'est pas un entier naturel, on ne l'initialise pas */
			if(taille <= 0)
				continue;

			if(tab != NULL){
				free(tab);
				tab = NULL;
			}

			tab = malloc(sizeof(int) * taille);
			lire(tab, taille);
		} else if(choix == 2)
		{
			afficher(tab, taille);
		} else if(choix == 3)
		{
			if(calcul_moyen(tab, taille) != -1)
				printf("Moyenne: %f", calcul_moyen(tab, taille));
		}

		printf("\n\n");
	} while(choix >= 1 && choix <= 3);

	return EXIT_SUCCESS;
}
