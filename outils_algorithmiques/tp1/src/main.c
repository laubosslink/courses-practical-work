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

	Fifo f = makeFifo(), f2 = makeFifo();

	printf("Empty? %d\n", emptyFifo(f));

	addFifoElmt(10, f);
	addFifoElmt(20, f);
	addFifoElmt(30, f);
	addFifoElmt(40, f);
	addFifoElmt(50, f);
	
	addFifoElmt(60, f2);
	addFifoElmt(70, f2);
	
	showFifo(f);
	showFifo(f2);
	
	printf("Empty? %d\n", emptyFifo(f));
	
	removeFifoElmt(f);
	showFifo(f);
	removeFifoElmt(f);
	removeFifoElmt(f);
	removeFifoElmt(f);
	showFifo(f);
		
	concatenate(f, f2);
	showFifo(f2);
	
	destruction(f2);
	showFifo(f2);
	addFifoElmt(100, f2);
	showFifo(f2);
	
	return 0;
}
