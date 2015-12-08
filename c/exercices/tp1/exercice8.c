#include <stdlib.h>
#include <stdio.h>
#include <math.h> // require -lm option

int main(){
	
	float a, b, c, delta;
	
	printf("Resolution eq. binomiale ax*x+b*x+c=0\n");
	printf("a: ");
	scanf("%f", &a);
	
	printf("b: ");
	scanf("%f", &b);
	
	printf("c: ");
	scanf("%f", &c);
	
	delta = b*b - 4*a*c;
	
	if(delta > 0)
	{
		printf("Il y a deux solutions:\n");
		printf("rac1: %f\n", (b*b+sqrt(delta))/(2*a));
		printf("rac2: %f\n", (b*b-sqrt(delta))/(2*a));
	} else if(delta == 0)
	{
		printf("Il y a une solution:\n");
		printf("rac0: %f\n", (-b)/(2*a));
	} else 
	{
		printf("Aucune solution\n");
	}
	
	return EXIT_SUCCESS;
}
