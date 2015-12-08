#include <stdio.h>
#include <stdlib.h>
#include <lifo.h>

int main(){

	int tests = 0;
	int* elmt;

    Lifo l = lifo_init();

/* test empty lifo */
	tests = lifo_is_empty(l) == 1;
#if DEBUG_AFFICHE == 1
    printf("empty : %d == 1\n", lifo_is_empty(l));
#endif

    elmt = (int*) malloc(sizeof(int));
    *elmt = 25;

    lifo_add_elmt(l, elmt);

    elmt = (int*) malloc(sizeof(int));
    *elmt = 27;

    lifo_add_elmt(l, elmt);

    elmt = (int*) malloc(sizeof(int));
    *elmt = 15;

    lifo_add_elmt(l, elmt);

    elmt = (int*) malloc(sizeof(int));
    *elmt = 17;

    lifo_add_elmt(l, elmt);


    elmt = (int*) malloc(sizeof(int));
    *elmt = 5;

    lifo_add_elmt(l, elmt);

    elmt = (int*) malloc(sizeof(int));
    *elmt = 7;

    lifo_add_elmt(l, elmt);

/* test function lifo_length */
    tests = lifo_length(l) == 6 && tests;

#if DEBUG_AFFICHE == 1
    printf("length : %d == 6\n", lifo_length(l));
#endif

/* test function lifo_head_elmt */
	tests = *(elmt = lifo_head_elmt(l)) == 7 && tests;

/* test order of pop */
#if DEBUG_AFFICHE == 1
    printf("return : %d == 7\n", *(elmt = lifo_head_elmt(l)));
#endif

	tests = *(elmt = lifo_pop_elmt(l)) == 7 && tests;

#if DEBUG_AFFICHE == 1
    printf("return : %d == 5\n", *(elmt = lifo_head_elmt(l)));
#endif

	tests = *(elmt = lifo_pop_elmt(l)) == 5 && tests;

/* test function lifo_length */
    tests = lifo_length(l) == 4 && tests;

#if DEBUG_AFFICHE == 1
    printf("length : %d == 4\n", lifo_length(l));
#endif

/* test function lifo_reverse */
    l = lifo_reverse(l);

#if DEBUG_AFFICHE == 1
    printf("pop reverse : %d == 25\n", *(elmt = lifo_head_elmt(l)));
#endif

    tests = *(elmt = lifo_pop_elmt(l)) == 25 && tests;

/* test function lifo_length */
    tests = lifo_length(l) == 3 && tests;

#if DEBUG_AFFICHE == 1
    printf("length : %d == 3\n", lifo_length(l));
#endif


	if(tests == 1)
		printf("lifo: \033[32mOK\033[0m\n");
	else
		printf("lifo: \033[31mproblemes durant les tests\033[0m\n");

	return 0;
}
