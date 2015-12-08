#include <stdio.h>
#include <stdlib.h>

#include "abr.h"

int main(){
	int tests = 0;
	FILE* f = fopen("./extra/dico.fr", "r");

	if(f != NULL){
		NOEUD n = chargement(f);

#if DEBUG_AFFICHE == 1
	show_debug_n_appel();
#endif

		tests = recherche_element(n, "hello");
		tests = recherche_element(n, "incursion") && tests;
		tests = !recherche_element(n, "incurse") && tests;
		tests = recherche_element(n, "zozo") && tests;
		
#if DEBUG_AFFICHE == 1
		printf("hello: %d == 1\n", recherche_element(n, "hello"));
		printf("incursion: %d == 1\n", recherche_element(n, "incursion"));
		printf("incurse: %d == 0\n", recherche_element(n, "incurse"));
		printf("zozo: %d == 1\n", recherche_element(n, "zozo"));
#endif

#if DEBUG_AFFICHE == 1
	show_debug_n_appel();
#endif

		fclose(f);
	} else {
		printf("FILE DOESNT EXIST\n");
	}
	
	if(tests == 1)
		printf("chargement(...): \033[32mOK\033[0m\n");
	else
		printf("chargement(...): \033[31mproblemes durant les tests\033[0m\n");
	
	if(tests)
		return EXIT_SUCCESS;

	return EXIT_FAILURE;
}
