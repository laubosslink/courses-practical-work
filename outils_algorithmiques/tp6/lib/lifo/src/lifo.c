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
 * @version 1.1
 * @date 12-05-2013
 */

/**
 * @file lifo.c
 *
 * Les fonctions permettant de manipuler la LIFO
 */

#include <stdlib.h>
#include <stdio.h>
#include <lifo.h>

struct Node {
    void* elmt;
    Node suivant;
};

struct Lifo {
    Node head;
};

Lifo lifo_init(){
    Lifo l = (Lifo) (malloc(sizeof(struct Lifo)));

    l->head = NULL;

    return l;
}

void lifo_add_elmt(Lifo l, void* elmt){
    if(l == NULL)
        fprintf(stderr, "Lifo pointer is null");

    if(l->head == NULL){
        l->head = (Node) malloc(sizeof(struct Node));
        l->head->elmt = elmt;
        l->head->suivant = NULL;
        return;
    }

    Node n = (Node) malloc(sizeof(struct Node));
    n->elmt = elmt;
    n->suivant = l->head;
    l->head = n;
    return;
}

void* lifo_pop_elmt(Lifo l){
    if(l == NULL || l->head == NULL)
        fprintf(stderr, "Lifo pointer is null");

    Node n;

    n = l->head;
    l->head = l->head->suivant;

    return n->elmt;
}

void* lifo_head_elmt(Lifo l){
	if(lifo_is_empty(l)){
		fprintf(stderr, "Lifo head pointer is null");
	}

	return l->head->elmt;
}

int lifo_is_empty(Lifo l){
    if(l == NULL || l->head == NULL)
        return 1;

    return 0;
}

int lifo_length(Lifo l){
    int n=0;

    if(lifo_is_empty(l))
        return 0;

    Node current = l->head;

    while(current != NULL){
        n++;
        current = current->suivant;
    }

    return n;
}

Lifo lifo_reverse(Lifo l){
    Lifo reverse = lifo_init();

    Node n = l->head;

    while(n != NULL){
        lifo_add_elmt(reverse, n->elmt);
        n = n->suivant;
    }

    return reverse;
}
