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
		f->tail = n;
		return;
	}
	
	/* Cas general si la file a plusieurs elements */
	n->next = f->tail->next;
	f->tail->next = n;
	f->tail = n;
	
	return;
}

void removeFifoElmt(Fifo f){
	/* Si la file est vide, on ne fait rien */
	if(emptyFifo(f))
		return;
	
	/* Cas ou la file a un seul element */
	if(f->tail->next == f->tail){
		free(f->tail);
		f->tail = NULL;
		return;
	}	
	
	/* Cas general si la file a plusieurs elements */
	Node n = f->tail->next;
	
	f->tail->next = f->tail->next->next;
	
	/* liberation memoire de l'element defile */
	free(n);
	
	return;
}

Node popFifoElmt(Fifo f){
	Node n;
	
	/* Si la file est vide, on ne fait rien */
	if(emptyFifo(f))
		return NULL;
	
	n = f->tail;
	
	/* Cas ou la file a un seul element */
	if(f->tail->next == f->tail){
		f->tail = NULL;
		return n;
	}	
	
	n = f->tail->next;
	
	/* Cas general si la file a plusieurs elements */
	f->tail->next = f->tail->next->next;
	
	return n;
}

void concatenate(Fifo f1, Fifo f2){
	/* Cas ou une des deux files est vide, on ne fait rien*/
	if(emptyFifo(f1) || emptyFifo(f2))
		return;
	
	/* Cas general si les files ont un ou plusieurs elements */
	Node n = f1->tail->next;
	
	f1->tail->next = f2->tail->next;
	
	f2->tail->next = n;
	
	f1->tail = f2->tail;
	
	return;
}

void showFifo(Fifo f){
	printf("{");
	
	/* Affichage vide si on a une fifo vide */
	if(emptyFifo(f)){
		printf("}\n");
		return;
	}
	
	/* Cas ou on a un seul element dans la file */
	if(f->tail->next == NULL || f->tail->next == f->tail){
		printf("%d", f->tail->value);
		printf("}\n");
		return;
	}
	
	/* Cas general si la file a plusieurs elements */
	Node n = f->tail->next;
	
	do {
		printf("%d, ", n->value);
		n = n->next;
	} while(n != NULL && n != f->tail);
	
	printf("%d", n->value);
	
	printf("}\n");
	
	return;
}

void destruction(Fifo f){
	/* Cas ou la file est vide , on ne fait rien*/
	if(emptyFifo(f))
		return;
	
	/* Cas si la file a un seul element*/
	if(f->tail->next == NULL || f->tail->next == f->tail)
	{
		free(f->tail);
		f->tail = NULL;
		return;
	} 
	
	/* Cas general si la file a plusieurs elements */
	Node n, n_next;
	
	n_next = f->tail;
	
	do {
		/* L'ordre est important ici, ne pas le changer ! */
		n = n_next; /* sauvegarde de l'adresse pour y faire un futur free */
		n_next = n_next->next;  /* on prend l'adresse "suivante" */
		
		/* on peut maintenant faire un free sur l'adresse sauvegarde,
		 * si celui si est realise avant, on ne connais plus le contenu de
		 * n_next, donc n_next->next peut ne plus marcher si
		 * en meme temps un autre programme ecris dans cette zone d'adresse memoire
		 */
		free(n); 
	} while(n_next != NULL && n_next != f->tail);

	f->tail = NULL;
	
	return;
}

int elmtIsPresent(int elmt, Fifo f){
	/* Cas ou la file est vide , on ne fait rien*/
	if(emptyFifo(f))
		return 0;
		
	/* Cas si la file a un seul element*/
	if(f->tail->next == NULL || f->tail == f->tail->next){
		if(f->tail->value == elmt)
			return 1;
		else
			return 0;
	}
	
	/* Cas general si la file a plusieurs elements */
	Node n = f->tail;

	do
	{
		if(n->value == elmt)
			return 1;

		n = n->next;
	} while(n != NULL && n != f->tail);

	return 0;
}
