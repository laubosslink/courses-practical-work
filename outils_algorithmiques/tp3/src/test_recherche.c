#include <stdlib.h>
#include <stdio.h>

#include "abr.h"

struct noeud {
	element valeur;
	NOEUD fils, frere;
};

NOEUD creer_arbre_test(){
	NOEUD a = (NOEUD) malloc(sizeof(struct noeud));
	
	/* ajout de "ca" et "ce" */
	a->valeur = 'c';
	a->fils = (NOEUD) malloc(sizeof(struct noeud));
	a->fils->valeur = 'a';
	a->fils->fils = (NOEUD) malloc(sizeof(struct noeud));
	a->fils->fils->valeur = '\0';
	a->fils->frere = (NOEUD) malloc(sizeof(struct noeud));
	a->fils->frere->valeur = 'e';
	a->fils->frere->fils = (NOEUD) malloc(sizeof(struct noeud));
	a->fils->frere->fils->valeur = '\0';
	
	/* ajout de "cela" et "ceci" */
	a->fils->frere->fils->frere = (NOEUD) malloc(sizeof(struct noeud));
	a->fils->frere->fils->frere->valeur = 'c';
	a->fils->frere->fils->frere->fils = (NOEUD) malloc(sizeof(struct noeud));
	a->fils->frere->fils->frere->fils->valeur = 'i';
	a->fils->frere->fils->frere->fils->fils = (NOEUD) malloc(sizeof(struct noeud));
	a->fils->frere->fils->frere->fils->fils->valeur = '\0';
	
	a->fils->frere->fils->frere->frere = (NOEUD) malloc(sizeof(struct noeud));
	a->fils->frere->fils->frere->frere->valeur = 'l';
	a->fils->frere->fils->frere->frere->fils = (NOEUD) malloc(sizeof(struct noeud));
	a->fils->frere->fils->frere->frere->fils->valeur = 'a';
	a->fils->frere->fils->frere->frere->fils->fils = (NOEUD) malloc(sizeof(struct noeud));
	a->fils->frere->fils->frere->frere->fils->fils->valeur = '\0';

	/* ajout "de" "du" "des" */
	a->frere = (NOEUD) malloc(sizeof(struct noeud));
	a->frere->valeur = 'd';
	a->frere->fils = (NOEUD) malloc(sizeof(struct noeud));
	a->frere->fils->valeur = 'e';
	a->frere->fils->fils = (NOEUD) malloc(sizeof(struct noeud));
	a->frere->fils->fils->valeur = '\0';
	a->frere->fils->fils->frere = (NOEUD) malloc(sizeof(struct noeud));
	a->frere->fils->fils->frere->valeur = 's';
	a->frere->fils->fils->frere->fils = (NOEUD) malloc(sizeof(struct noeud));
	a->frere->fils->fils->frere->fils->valeur = '\0';
	
	a->frere->fils->frere = (NOEUD) malloc(sizeof(struct noeud));
	a->frere->fils->frere->valeur = 'u';
	a->frere->fils->frere->fils = (NOEUD) malloc(sizeof(struct noeud));
	a->frere->fils->frere->fils->valeur = '\0';
	
	return a;
}

int main(){
	int tests = 1;
	NOEUD a = creer_arbre_test();

#if DEBUG_AFFICHE == 1
	printf("ca: %d == 1\n", recherche_element(a, "ca"));
	printf("ce: %d == 1\n", recherche_element(a, "ce"));
	printf("ci: %d == 0\n", recherche_element(a, "ci"));
	printf("ces: %d == 0\n", recherche_element(a, "ces"));
	printf("d: %d == 0\n", recherche_element(a, "d"));
	printf("cela: %d == 1\n", recherche_element(a, "cela"));
	printf("celaa: %d == 0\n", recherche_element(a, "celaa"));
	printf("ceci: %d == 1\n", recherche_element(a, "ceci"));
	printf("cec: %d == 0\n", recherche_element(a, "cec"));
	printf("de: %d == 1\n", recherche_element(a, "de"));
	printf("du: %d == 1\n", recherche_element(a, "du"));
	printf("des: %d == 1\n", recherche_element(a, "des"));
#endif

	tests = recherche_element(a, "ca") && tests;
	tests = recherche_element(a, "ce") && tests;
	tests = recherche_element(a, "ci") == 0 && tests;
	tests = recherche_element(a, "ces") == 0 && tests;
	tests = recherche_element(a, "cela") == 1 && tests;
	tests = recherche_element(a, "celaa") == 0 && tests;
	tests = recherche_element(a, "d") == 0 && tests;
	tests = recherche_element(a, "ceci") == 1 && tests;
	tests = recherche_element(a, "cec") == 0 && tests;
	tests = recherche_element(a, "de") == 1 && tests;
	tests = recherche_element(a, "du") == 1 && tests;
	tests = recherche_element(a, "des") == 1 && tests;
		
#if DEBUG_AFFICHE == 1
	show_debug_n_appel();
#endif

	if(tests == 1)
		printf("recherche(...): \033[32mOK\033[0m\n");
	else
		printf("recherche(...): \033[31mproblemes durant les tests\033[0m\n");
	
	return 0;
}
