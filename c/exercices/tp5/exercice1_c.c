#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

typedef struct infoReduction {
	int index, value;
	struct infoReduction *node;
} infoReduction;

void expansion(infoReduction *ir, int **tab){
	int i, initSize;
	
	if(ir->index != -1)
		fprintf(stderr, "erreur dans l'expansion, mauvais placement sur index, la taille ne peut etre determine");
	
	initSize = ir->value;
	//ir=ir->node; // TODO checks
	
	*tab = malloc(sizeof(int) * initSize);
	
	for(i=0; i<initSize; i++){
		if(i == ir->index){
			(*tab)[i] = ir->value;
			ir = ir->node;
		} else {
			(*tab)[i] = 0;
		}
	}
}

int effacerZeros(int tab[], int taille){
	int i, x;
	
	for(i=0; i<taille; i++)
	{
		/* dès qu'on arrive sur un 0 */
		if(tab[i] == 0){
			/* on regarde si il y en a après */
			for(x=1; i+x < taille && tab[i+x] == 0; x++);
			
			/* si il n'y a eu que des 0 après, on a atteint le bout du tableau, on affiche où on s'est arrêté */
			if(i+x == taille) return i;
			
			/* on échange le 0 avec une valeur trouvé*/
			tab[i] = tab[i+x];
			tab[i+x] = 0;
		}
	}
	
	/* si il n'y  aucun 0 */
	return taille;
}

int reduction(infoReduction *ir, int *tab, int taille){
	int i;
	
	infoReduction *current = ir;
	
	ir->index = -1;
	ir->value = taille;
	
	if(ir->node == NULL){
		ir->node = malloc(sizeof(infoReduction));
	}
	
	current = ir->node;
	
	for(i=0; i<taille; i++){
			if(tab[i] != 0){
				current->index = i;
				current->value = tab[i];
				current->node = malloc(sizeof(infoReduction));
			}
	}
	
	return effacerZeros(tab, taille);
	
	//free(current->node);
	//current->node = NULL;
	// TODO 
}

void afficheTable(int tab[], int taille){
		int i;
		
        printf("{");
        
        for(i=0; i<taille;i ++){
                printf("%d,", tab[i]);
        }
        
        printf("}\n\n");
}

void initTab(int **tab, int taille){
	int i, number;
	
	*tab = malloc(sizeof(int) * taille);
	
	for(i=0; i<taille; i++){
		if(rand()%100 >= 90){
			number = rand()%2000;
			
			if(number >= 1000) 
				number *= -1;
			(*tab)[i] = number;
		} else {
			(*tab)[i] = 0;
		}
	}
}

void reductionMemoire(int **tab, int nouvelleTaille){
	*tab = realloc(*tab, sizeof(int) * nouvelleTaille);
}

int main(){
	int taille=pow(10, 1); // 10^7
	int *tab; 
	infoReduction *ir;
	
	srand(time(NULL));
	
	initTab(&tab, taille);
	afficheTable(tab, taille);
	//taille = effacerZeros(tab, taille);
	//reductionMemoire(&tab, taille);
	
	
	ir = malloc(sizeof(infoReduction));
	taille = reduction(ir, tab, taille);
	expansion(ir, &tab);
	afficheTable(tab, taille);
	
	return EXIT_SUCCESS;
}
