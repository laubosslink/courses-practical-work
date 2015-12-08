#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, i;

	printf("n:");
	scanf("%d", &n);

	i = n;

	// Si un nombre negatif est rentre on ne rentre pas dans la boucle

	while(i >= 0){
		printf("%d,", i);
		i--;
	}

	printf("\n");

	return EXIT_SUCCESS;
}
