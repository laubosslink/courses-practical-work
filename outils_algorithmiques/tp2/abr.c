/*****************************************************************************/
/*   C. PORQUET                     ABR_TP.c                   Novembre 2012 */
/*                      Arbres binaires de recherche                         */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "abr.h"
#include "file.h"

struct noeud {
	element valeur;
	NOEUD *gauche, *droit;
};

/*****************************************************************************/
NOEUD *arbre_vide() {return NULL; }
/*****************************************************************************/
element arbre_get_element(NOEUD *p) {
	if(p == NULL)
		return 0;
		
	return p->valeur;
}
/*****************************************************************************/
NOEUD *insere(NOEUD *p, element x)
{if (p == NULL) 
    {p = (NOEUD *)malloc(sizeof(NOEUD));
     p->valeur = x;p->gauche = NULL;p->droit = NULL;
    }
 else if (x == p->valeur) printf("%d est deja dans l'arbre\n",x);
      else if (x < p->valeur)  p->gauche = insere(p->gauche,x);
                          else p->droit  = insere(p->droit,x);
			  
return(p);			  
}
/*****************************************************************************/
void parcour_RGD(NOEUD *p){
	if(!p) return;
	
	printf("%d\n", p->valeur);
	parcour_RGD(p->gauche);
	parcour_RGD(p->droit);
}
/*****************************************************************************/
void parcour_GRD(NOEUD *p){
	if(!p) return;
	
	parcour_GRD(p->gauche);
	printf("%d\n", p->valeur);
	parcour_GRD(p->droit);
}
/*****************************************************************************/
void parcour_GDR(NOEUD *p){
	if(!p) return;
	
	parcour_GDR(p->gauche);
	parcour_GDR(p->droit);
	printf("%d\n", p->valeur);
}
/*****************************************************************************/
int compter_RGD_GDR(NOEUD *p){
	if(p == NULL){
		return 0;
	}	
	
	int v = 1;

	printf("prefixe: %d\n", p->valeur);
	
	v += compter_RGD_GDR(p->gauche);
	v += compter_RGD_GDR(p->droit);
	
	printf("suffixe: %d\n", p->valeur);
	
	return v;
}
/*****************************************************************************/
void parcour_largeur(NOEUD *p){
	Filo f = makeFilo();
	
	addFiloElmt(p, f);
	while(!emptyFilo(f)){
		p = popFiloElmt(f);
		
		printf("%d \n", p->valeur);
		
		if(p->gauche != NULL)
			addFiloElmt(p->gauche, f);
			
		if(p->droit != NULL)
			addFiloElmt(p->droit, f);
	}
}
/*****************************************************************************/
Filo bordure(NOEUD *p){
	Filo f = makeFilo();
	
	if(p == NULL)
		return f;
	
	if(p->gauche == NULL && p->droit == NULL){
		addFiloElmt(p, f);
		return f;
	}
	
	//if(p->gauche != NULL)
		concatenate(bordure(p->gauche), f);
		
	//if(p->droit != NULL)
		concatenate(bordure(p->droit), f);
		
	return f;
} 
/*****************************************************************************/
void affiche_arbre(NOEUD *p, int col)
{int i;
 if (p)
    {affiche_arbre(p->droit,col+1);
     for (i=0;i<col;i++) printf("   ");
     printf("%d\n",p->valeur);
     affiche_arbre(p->gauche,col+1);
    }  	
}
/*****************************************************************************/
