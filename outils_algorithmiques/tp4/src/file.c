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
 * @file file.c
 *
 * Les fonctions permettant de manipuler la FIFO
 */

#include <stdlib.h>
#include <stdio.h>
#include <file.h>

struct Node {
	int value;
	Node next;
};

struct Fifo {
	Node tail;
};

Fifo makeFifo(){
	Fifo f = (Fifo) malloc(sizeof(struct Fifo));

	f->tail = NULL;

	return f;
}

int emptyFifo(Fifo f){
	return (f == NULL || f->tail == NULL);
}

void addFifoElmt(int value, Fifo f){
	Node n = (Node) malloc(sizeof(struct Node));

	n->value = value;

	/* Cas ou la fifo est vide, et on ajoute le premier element */
	if(emptyFifo(f)){
		n->next = n;
	} else {
		n->next = f->tail->next;
		f->tail->next = n;
	}

	f->tail = n;
}

void removeFifoElmt(Fifo f){
	Node n = f->tail->next;

	/* Si la file est vide, on ne fait rien */
	if(emptyFifo(f))
		return;

	/* Cas ou la file a un seul element */
	if(f->tail->next == f->tail){
		free(f->tail);
		f->tail = NULL;
		return;
	}

	f->tail->next = f->tail->next->next;

	/* liberation memoire de l'element defile */
	free(n);
}

int popFifoElmt(Fifo f){
	Node n = f->tail->next;

	/* Si la file est vide, on ne fait rien */
	if(emptyFifo(f))
		return -1;

	/* Cas ou la file a un seul element */
	if(f->tail->next == f->tail){
		f->tail = NULL;
		return n->value;
	}

	f->tail->next = f->tail->next->next;

	return n->value;
}

void concatenate(Fifo f1, Fifo f2){
	Node n;

	/* Cas ou une des deux files est vide, on ne fait rien*/
	if(emptyFifo(f1) || emptyFifo(f2))
		return;

	n = f1->tail->next;

	f1->tail->next = f2->tail->next;

	f2->tail->next = n;

	f1->tail = f2->tail;
}

void showFifo(Fifo f){
	Node n;

	printf("{");

	/* Affichage vide si on a une fifo vide */
	if(emptyFifo(f)){
		printf("}\n");
		return;
	}

	/* Cas ou on a un seul element dans la file */
	if(f->tail->next == f->tail){
		printf("%d, ", f->tail->value);
		printf("}\n");
		return;
	}

	n = f->tail->next;

	do {
		printf("%d, ", n->value);
		n = (Node) n->next;
	} while(n != NULL && n != f->tail);

	printf("%d", n->value);

	printf("}\n");
}

void destruction(Fifo f){
	Node n, n_next;

	if(emptyFifo(f))
		return;

	n_next = f->tail->next;

	do {
		n = n_next;
		free(n);
		n_next = (Node) n_next->next;
	} while(n_next != NULL && n_next != f->tail);

	f->tail = NULL;
}

