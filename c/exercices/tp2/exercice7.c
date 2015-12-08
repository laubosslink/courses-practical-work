#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	float a, b, somme;
	unsigned long int n;
	
	b = 1.0;
	somme = b;
	n=1;
	
	do
	{
		a=b;
		n++;
		b = (1.0 / n) * (1.0 / n);
		somme += b;
	} while(a != b);

	printf("n: %ld\n", n);
	printf("somme : %.18f\n", somme);
	printf("somme d'apres definition d'euler : %.18f\n", (M_PI*M_PI)/6);
	
	return EXIT_SUCCESS;
}
