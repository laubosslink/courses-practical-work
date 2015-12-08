#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, i;

	printf("n:");
	scanf("%d", &n);

	// Si un nombre negatif est rentre on ne rentre pas dans la boucle

	for(i=n; i>=0; i--)
		printf("%d,", i);

	printf("\n");

	return EXIT_SUCCESS;
}
