#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void afficheTable(int tab[], int taille){
        int i=0;

        printf("{");
        for(; i<taille;i ++){
                printf("%d,", tab[i]);
        }
        
        printf("}\n\n");
}

int effacerZeros(int tab[], int taille){
	int i, x;
	
	for(i=0; i<taille; i++)
	{
		/* dès qu'on arrive sur un 0 */
		if(tab[i] == 0){
			/* on regarde si il y en a après */
			for(x=1; tab[i+x] == 0 && i+x < taille; x++);
			
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

void reductionMemoire(int *tab, int nouvelleTaille){
	tab = realloc(tab, sizeof(int) * nouvelleTaille);
}

void initTab(int *tab, int taille){
	int i, number;
	
	srand(time(NULL));
	
	for(i=0; i<taille; i++){
		if(rand()%100 >= 90){
			number = rand()%2000;
			
			if(number >= 1000) 
				number *= -1;
			
			tab[i] = number;
		} else {
			tab[i] = 0;
		}
	}
}

int main(){
	int taille, tailleOrigine=pow(10, 7);
	int *tab = malloc(sizeof(int) * tailleOrigine);
	
	initTab(tab, tailleOrigine);
	taille = effacerZeros(tab, tailleOrigine);
	reductionMemoire(tab, taille);
	
	printf("taille finale : %d\n", taille);
	
	return EXIT_SUCCESS;
}
