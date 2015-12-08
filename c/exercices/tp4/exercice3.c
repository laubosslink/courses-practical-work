#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "exercice3.h"
#include "swap.h"

void initTabAlea(Tab *t, int taille){
	int i;
	
	t->nbr = taille;
	t->maxi = taille;
	t->cont = malloc(sizeof(long) * taille);
	
	srand(time(NULL));
	
	for(i=0; i<taille; i++){
		t->cont[i] = rand();
	}
}

void afficherTab(Tab *t){
	int i;
	
	for(i=0; i<t->nbr; i++){
		printf("%ld\t", t->cont[i]);
	}
}

int validerTri(Tab *t){
	int i;
	
	for(i=0; i<t->nbr-1; i++){
		if(t->cont[i] > t->cont[i+1])
			return 0;
	}
	
	return 1;
}

void triSelection(Tab *t){
	int i, j, min;
	
	for(i=0; i<t->nbr; i++){
		min = i;
		
		for(j=i+1; j<t->nbr; j++)
		{
			if(t->cont[j] < t->cont[min])
				min = j;
		}
		
		if(min != i)
			lswap(t->cont+i, t->cont+min);
	}
}

void triInsertion(Tab *t){
	int i, j, x;
	
	for(i=1; i<t->nbr; i++)
	{
		x = t->cont[i];
		
		// faire while
		for(j=i; j > 0 && t->cont[j-1] > x; j--){
			t->cont[j] = t->cont[j-1];
		}
		
		t->cont[j] = x;
	}
}

void triEchange(Tab *t){
	int echange, j;
	
	do{
		echange = 0;
		for(j=0; j<t->nbr-1; j++){
			if(t->cont[j] > t->cont[j+1]){
				lswap(t->cont+j, t->cont+j+1);
				echange=1;
			}
		}
	} while(echange);
}

void copyTab(Tab *t1, Tab *t2){
	int i;
	
	initTabAlea(t2, t1->nbr);
	
	for(i=0; i<t1->nbr; i++){
		t2->cont[i] = t1->cont[i];
	}
}

int exercice3(){
	Tab *t, t2[3];
	int taille[5] = {5000, 7500, 10000, 12500, 15000};
	int i, n;
	
	clock_t time;
	
	/*
	t = malloc(sizeof(Tab) * 100);
	
	for(i=0; i<100; i++){
		initTabAlea(&(t[i]), 100);
		triSelection(&(t[i]));
		
		if(!validerTri(t+i)){
			printf("Il y a un tableau non trié le n°%d du tri par selection!\n", i);
			return EXIT_FAILURE;
		}
	}
	
	for(i=0; i<100; i++){
		initTabAlea(&(t[i]), 100);
		triInsertion(&(t[i]));
		
		if(!validerTri(&(t[i]))){
			printf("Il y a un tableau non trié le n°%d du tri par insertion !\n", i);
			return EXIT_FAILURE;
		}
	}
	
	for(i=0; i<100; i++){
		initTabAlea(&(t[i]), 100);
		triEchange(&(t[i]));
		
		if(!validerTri(&(t[i]))){
			printf("Il y a un tableau non trié le n°%d du tri par échange !\n", i);
			return EXIT_FAILURE;
		}
	}
	
	printf("Aucun problème, les 1000 tableaux sont triés\n");
	*/
	
	for(i=0; i<5; i++){
		n=taille[i];
		initTabAlea(t2, n);
		copyTab(t2, t2+1);
		copyTab(t2+1, t2+2);
		
		time=clock();
		triSelection(t2);
		time=((clock()-time) / 1000000.0F) * 1000;
		printf("selection: %d %f\n", n, (float)time);
		
		time=clock();
		triInsertion(t2+1);
		time=((clock()-time) / 1000000.0F) * 1000;
		printf("insertion: %d %f\n", n, (float)time);
		
		time=clock();
		triEchange(t2+2);
		time=((clock()-time) / 1000000.0F) * 1000;
		printf("echange: %d %f\n", n, (float)time);
	}
	
	return EXIT_SUCCESS;
}
