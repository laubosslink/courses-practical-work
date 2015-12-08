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
 * @file pile.c
 * 
 * Les fonctions permettant de manipuler la Filo
 */

#include <stdlib.h>
#include <stdio.h>

#include "abr.h"
#include "file.h"

struct Node {
	NOEUD* value;
	Node next;
};

struct Filo {
	Node tail;
};

Filo makeFilo(){
	Filo f = (Filo) malloc(sizeof(struct Filo));
	
	f->tail = NULL;
	
	return f;
}

int emptyFilo(Filo f){
	return (f == NULL || f->tail == NULL);
}

void addFiloElmt(NOEUD* value, Filo f){
	Node n = (Node) malloc(sizeof(struct Node));
	
	n->value = value;
	
	/* Cas ou la Filo est vide, et on ajoute le premier element */	
	if(emptyFilo(f)){
		n->next = n;
	} else {
		n->next = f->tail->next;		
		f->tail->next = n;
	}
	
	f->tail = n;
}

void removeFiloElmt(Filo f){
	Node n = f->tail->next;
	
	/* Si la file est vide, on ne fait rien */
	if(emptyFilo(f))
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

NOEUD* popFiloElmt(Filo f){
	Node n = f->tail->next;
	
	/* Si la file est vide, on ne fait rien */
	if(emptyFilo(f))
		return NULL;
	
	/* Cas ou la file a un seul element */
	if(f->tail->next == f->tail){
		f->tail = NULL;
		return n->value;
	}	
	
	f->tail->next = f->tail->next->next;
	
	return n->value;
}

void concatenate(Filo f1, Filo f2){
	Node n;
	
	/* Cas ou une des deux files est vide, on ne fait rien*/
	if(emptyFilo(f1) || emptyFilo(f2))
		return;
	
	//printf("%d, %d, ", f1->tail->value->valeur, f2->tail->value->valeur);
	
	n = f1->tail->next;
	
	f1->tail->next = f2->tail->next;
	
	f2->tail->next = n;
	
	f1->tail = f2->tail;
}

void showFilo(Filo f){
	Node n;
	
	printf("{");
	
	/* Affichage vide si on a une Filo vide */
	if(emptyFilo(f)){
		printf("}");
		return;
	}
	
	/* Cas ou on a un seul element dans la file */
	if(f->tail->next == f->tail){
		printf("%d, ", arbre_get_element(f->tail->value));
		printf("}\n");
		return;
	}
		
	n = f->tail->next;
	
	do {
		printf("%d, ", arbre_get_element(n->value));
		n = (Node) n->next;
	} while(n != NULL && n != f->tail);
	
	printf("%d", arbre_get_element(n->value));
	
	printf("}\n");
}
