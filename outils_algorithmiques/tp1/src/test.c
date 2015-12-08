/**
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 * 
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written premission of the authors
 */
 
/**
 * @author PARMENTIER Laurent <parmentier@ecole.ensicaen.fr, laubosslink@society-lbl.com>
 * @author EL HIMDI Yasmine <yasmine.elhimdi@ecole.ensicaen.fr>
 * @version 1.0 
 * @date 03-02-2013
 */
 
/** 
 * @file main.c
 * 
 * Manipulation de la fifo (file)
 */

#include <stdlib.h>
#include <stdio.h>
#include <file.h>

int main(){
	int tests = 0;

	Fifo f1 = makeFifo();

	Fifo f2 = makeFifo();

	tests = (emptyFifo(f1) && emptyFifo(f2));

#if DEBUG_AFFICHE == 1
	printf("empty(f1): %d == 1\n", emptyFifo(f1));
	printf("empty(f2): %d == 1\n\n", emptyFifo(f2));
#endif

#if DEBUG_AFFICHE == 1
	printf("We add : 10, 20, 30, 40, 50 in 'f1'\n");
	printf("We add : 60, 70 in 'f2'\n\n");
#endif

	addFifoElmt(10, f1);
	addFifoElmt(20, f1);
	addFifoElmt(30, f1);
	addFifoElmt(40, f1);
	addFifoElmt(50, f1);

	addFifoElmt(60, f2);
	addFifoElmt(70, f2);

#if DEBUG_AFFICHE == 1
	printf("f1 contain : ");
	showFifo(f1);
	printf("\n");

	printf("f2 contain : ");
	showFifo(f2);
	printf("\n");
#endif

	tests = (elmtIsPresent(10, f1) && tests);
	tests = (elmtIsPresent(20, f1) && tests);
	tests = (elmtIsPresent(30, f1) && tests);
	tests = (elmtIsPresent(40, f1) && tests);
	tests = (elmtIsPresent(50, f1) && tests);

	tests = (elmtIsPresent(60, f2) && tests);
	tests = (elmtIsPresent(70, f2) && tests);

	tests = (emptyFifo(f1) == 0 && emptyFifo(f2) == 0 && tests);

#if DEBUG_AFFICHE == 1
	printf("empty(f1): %d == 0\n", emptyFifo(f1));
	printf("empty(f2): %d == 0\n", emptyFifo(f2));
#endif

#if DEBUG_AFFICHE == 1
	printf("\nWe remove one elmt from 'f1'\n");
	printf("'f1' must contain : 20, 30, 40, 50\n");
#endif
	removeFifoElmt(f1);

#if DEBUG_AFFICHE == 1
	printf("'f1' contain : ");
	showFifo(f1);
#endif
	tests = (elmtIsPresent(20, f1) && tests);
	tests = (elmtIsPresent(30, f1) && tests);
	tests = (elmtIsPresent(40, f1) && tests);
	tests = (elmtIsPresent(50, f1) && tests);

#if DEBUG_AFFICHE == 1
	printf("\nWe remove three elmt from 'f1'\n");
	printf("'f1' must contain : 50\n");
#endif

	removeFifoElmt(f1);
	removeFifoElmt(f1);
	removeFifoElmt(f1);

#if DEBUG_AFFICHE == 1
	printf("'f1' contain : ");
	showFifo(f1);
#endif
	tests = (elmtIsPresent(50, f1) && tests);

#if DEBUG_AFFICHE == 1
	printf("\nWe concatenate 'f1' with 'f2' in 'f2'\n");
	printf("'f2' must contain : 50, 60, 70\n");
#endif

	concatenate(f1, f2);

#if DEBUG_AFFICHE == 1
	printf("'f2' contain : ");
	showFifo(f2);
#endif

	tests = (elmtIsPresent(50, f1) && tests);
	tests = (elmtIsPresent(60, f1) && tests);
	tests = (elmtIsPresent(70, f1) && tests);

#if DEBUG_AFFICHE == 1
	printf("\ndestruction 'f2'\n");
#endif

	destruction(f2);

#if DEBUG_AFFICHE == 1
	printf("'f2' contain : ");
	showFifo(f2);
#endif

#if DEBUG_AFFICHE == 1
	printf("\nWe add : 80, 90 in 'f2'\n\n");
#endif

	addFifoElmt(80, f2);
	addFifoElmt(90, f2);

#if DEBUG_AFFICHE == 1
	printf("f2 contain : ");
	showFifo(f2);
#endif

	tests = (elmtIsPresent(80, f2) && tests);
	tests = (elmtIsPresent(90, f2) && tests);

	tests = (emptyFifo(f2) == 0 && tests);

#if DEBUG_AFFICHE == 1
	printf("empty(f2): %d == 0\n", emptyFifo(f2));
#endif

	removeFifoElmt(f2);
	concatenate(f1, f2);
	
	tests = (elmtIsPresent(90, f2) && tests);
	//tests = (elmtIsPresent(50, f2) && tests);
	
	if(tests){
		printf("file.c: \033[32mOK\033[0m\n");
		return EXIT_SUCCESS;
	}

	printf("file.c: \033[31mproblemes durant les tests\033[0m\n");
	return EXIT_FAILURE;

}

