#include <stdlib.h>
#include <stdio.h>

void afficheTable(int tab[], int taille){
        int i;

        printf("{");
        for(i=0; i<taille;i ++){
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

int main(){
	int taille, tailleOrigine=18;
	
	int tab[] = {3,4,0,0,5,0,6,7,8,0,0,9,0,0,0,0,1,2};
	//int tab[] = {3,4,6,4,5,3,6,7,8,2,1,9,5,6,1,1,1,2};
	//int tab[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	//int tab[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	//int tab[] = {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	afficheTable(tab, tailleOrigine);
	taille = effacerZeros(tab, tailleOrigine);
	afficheTable(tab, taille);
	
	printf("taille finale : %d\n", taille);
	
	return EXIT_SUCCESS;
}
