#include <stdio.h>
#include <stdlib.h>

int main(void){
	int n, y=0, x;

	printf("Saisir le nombre de lignes:");
	scanf("%d", &n);

	for(; y<n; y++)
	{
		for(x=0; x<=y; x++){
			printf("*");
		}

		printf("\n");
	}

	return EXIT_SUCCESS;
}
