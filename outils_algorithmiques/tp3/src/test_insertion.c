#include <stdio.h>

#include "abr.h"

int main(){
	int tests = 0;
	
	NOEUD a = creer_arbre();
	
	insertion_element(a, "ca");
	tests = recherche_element(a, "ca");
#if DEBUG_AFFICHE == 1
	printf("ca: %d == 1\n", recherche_element(a, "ca"));
#endif
	
	insertion_element(a, "ce");
	tests = recherche_element(a, "ce") && tests;
#if DEBUG_AFFICHE == 1
	printf("ce: %d == 1\n", recherche_element(a, "ce"));
#endif

	insertion_element(a, "cela");
	tests = recherche_element(a, "cela") && tests;
#if DEBUG_AFFICHE == 1
	printf("cela: %d == 1\n", recherche_element(a, "cela"));
#endif

	insertion_element(a, "ceci");
	tests = recherche_element(a, "ceci") && tests;
#if DEBUG_AFFICHE == 1
	printf("ceci: %d == 1\n", recherche_element(a, "ceci"));
#endif

	insertion_element(a, "de");
	tests = recherche_element(a, "de") && tests;
#if DEBUG_AFFICHE == 1
	printf("de: %d == 1\n", recherche_element(a, "de"));
#endif

	insertion_element(a, "du");
	tests = recherche_element(a, "du") && tests;
#if DEBUG_AFFICHE == 1
	printf("du: %d == 1\n", recherche_element(a, "du"));
#endif

	insertion_element(a, "des");
	tests = recherche_element(a, "des") && tests;
#if DEBUG_AFFICHE == 1
	printf("des: %d == 1\n", recherche_element(a, "des"));
#endif
		
#if DEBUG_AFFICHE == 1
	show_debug_n_appel();
#endif

	if(tests == 1)
		printf("insertion(...): \033[32mOK (etape 1)\033[0m\n");
	else
		printf("insertion(...): \033[31mproblemes durant les tests\033[0m\n");
	

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
	printf("det: %d == 0\n", recherche_element(a, "det"));
	printf("c: %d == 0\n", recherche_element(a, "c"));
#endif

	tests = recherche_element(a, "ca");
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
	tests = recherche_element(a, "det") == 0 && tests;
	tests = recherche_element(a, "c") == 0 && tests;

	if(tests == 1)
		printf("insertion(...): \033[32mOK (etape 2)\033[0m\n");
	else
		printf("insertion(...): \033[31mproblemes durant les tests\033[0m\n");
	
	return 0;
}
