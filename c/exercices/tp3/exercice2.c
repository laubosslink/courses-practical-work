#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void effacerLigneCourante(int k){
	int j;

	for(j=0; j<k; j++){
		printf("\b");
	}

	for(j=0; j<k; j++){
		printf(" ");
	}

	for(j=0; j<k; j++){
		printf("\b");
	}
}

void exercice2(){
	int n, i=0, j, rand_n;

	printf("Nombre de fois où la barre de longueur variable devra être affichée: ");
	scanf("%d", &n);

	srand(time(NULL));

	for(; i<n; i++)
	{
		rand_n = rand()%80;

		for(j=0; j<rand_n; j++)
		{
			printf("*");
		}
		fflush(stdout);

		sleep(1);

		effacerLigneCourante(rand_n);
	}

}
