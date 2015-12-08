#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "abr.h"

int main()
{
	NOEUD *a[3]; /* on peut travailler sur 3 arbres */
	char c;
	int i, j;
	element x;
	char nom_fich[20];
	FILE *fich;

	a[0] = arbre_vide();
	a[0] = insere(a[0], 15);
	a[0] = insere(a[0], 10);
	a[0] = insere(a[0], 20);
	a[0] = insere(a[0], 5);
	a[0] = insere(a[0], 12);
	a[0] = insere(a[0], 17);
	a[0] = insere(a[0], 25);
	a[0] = insere(a[0], 11);

	do {printf("Commande ? "); c = getchar();
	 switch(c)
	 {
	  case 'v' : scanf("%d",&i); a[i] = arbre_vide(); break;     
	  case 'i' : scanf("%d %d",&x,&i); a[i] = insere(a[i],x); break;    
	  case 'a' : scanf("%d",&i); affiche_arbre(a[i],1); break;          
	  case 'g' : scanf("%d",&i); parcour_RGD(a[i]); break;          
	  case 'r' : scanf("%d",&i); parcour_GRD(a[i]); break;           
	  case 'd' : scanf("%d",&i); parcour_GDR(a[i]); break;           
	  case 'c' : scanf("%d",&i); printf("nbr: %d\n", compter_RGD_GDR(a[i])); break;     
	  case 'p' : scanf("%d",&i); parcour_largeur(a[i]); break;              
	  case 'b' : scanf("%d",&i); showFilo(bordure(a[i])); break;
	  case 'q' : exit(0); 
	 }
	 printf("\n"); c = getchar();
	}
	while (1);
}
