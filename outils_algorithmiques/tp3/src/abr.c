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
 * @file abr.c
 * 
 * Les fonctions permettant de manipuler l'arbre
 */

#include <stdio.h>
#include <stdlib.h>

#include "abr.h"

struct noeud {
	element valeur;
	NOEUD fils, frere;
};


#if DEBUG_AFFICHE == 1
int debug_n_appel=0;

void show_debug_n_appel(){
	printf("debug_n_appel: %d\n", debug_n_appel);
	debug_n_appel=0;
}
#endif

NOEUD creer_arbre_element(element e){
	NOEUD na; /* noeud allocation */
	
	na = malloc(sizeof(struct noeud));
	
	na->valeur = e;
	na->fils = NULL;
	na->frere = NULL;
	
	return na;
}

NOEUD creer_arbre(){
	return creer_arbre_element('\0');
}

int recherche_element(NOEUD n, char* str){

#if DEBUG_AFFICHE == 1
	debug_n_appel++;
#endif
	
	/* si un noeud n'a rien, c'est que l'element n'est pas dans l'arbre */
	if(n == NULL)
		return 0;
	
	/* si on arrive a la fin de la chaine de caractere, c'est que le mot est dans l'arbre */
	if(*str == '\0' && n->valeur == '\0')
		return 1;
		
#if DEBUG_AFFICHE == 1 && DEBUG_OPTIMISE == 1
//	Permet de reduire le nombre d'appel mais est-ce vraiment optimise avec le nombre d'appel recursif de la condition ?	non
	if(*str == '\0' && *(str+1) != '\0')
		return 0;
#endif

	/* lorsque la valeur actuelle n'est pas egale au caractere actuel on regarde le frere */
	if(n->valeur != *str)
		return recherche_element(n->frere, str);
	
	/* si la condition precedente n'est pas verifie,
	 * la valeur actuelle est egale au caractere actuel, on regarde doc le fils, 
	 * et on passe au caractere suivant de la chaine de caractere 
	 */
	return recherche_element(n->fils, str+1);
}

int noeud_vide(NOEUD n){
	return n->valeur == '\0' && n->fils == NULL && n->frere == NULL;
}

NOEUD insertion_element(NOEUD n, char* str){
	if(noeud_vide(n)){
		n->valeur = *str;
		insertion_element_rec(n, str);
	} else {
		insertion_element_rec(n, str);
	}
	
	return n;
	
}

void insertion_element_rec(NOEUD n, char* str){

#if DEBUG_AFFICHE == 1
	debug_n_appel++;
#endif

	if(*str == '\0')
		return;
	
	if(n->valeur == *str){
		if(n->fils == NULL)
			n->fils = creer_arbre_element(*(str+1));

		insertion_element_rec(n->fils, str+1);
		
		return;
	}	

	if(n->frere == NULL)
			n->frere = creer_arbre_element(*(str));

	insertion_element_rec(n->frere, str);
}

NOEUD chargement(FILE *f){
	NOEUD n = creer_arbre();
	
	char* mot;
	char c;
	
	mot = (char*) malloc(sizeof(char) * 100);

	while((c = getc(f)) != EOF){
		fseek(f, -1, SEEK_CUR);
		fscanf(f, "%s\n", mot);
		insertion_element(n, mot);
	}
	
	return n;
}

