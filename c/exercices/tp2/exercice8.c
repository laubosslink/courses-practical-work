#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
	int c;
	
	c = *b;
	*b = *a;
	*a = c;
}

int pgcd(int a, int b)
{
	int r;
	
	if(a < b)
		swap(&a, &b);
	
	while(b > 0)
	{
		r = a % b;
		a = b;
		b = r;
	}
	
	return a;
}

int main()
{
	int a, b;
	
	printf("Veuillez entrer deux nombres\n");
	
	printf("a:");
	scanf("%d", &a);
	printf("b:");
	scanf("%d", &b);
	
	printf("pgcd(%d, %d) = %d\n", a, b, pgcd(a, b));
	
	return EXIT_SUCCESS;
}
