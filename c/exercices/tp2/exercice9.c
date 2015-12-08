#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* prop 1 fausse, addition de decimale au depart...
int addition(int a, int b, int base){
	int tmp, n, output;
	n=0;
	
	tmp = a + b;
	output = 0;
	
	while(tmp > 0)
	{
		output += (tmp%base) * pow(10, n);
		tmp /= base;
		n++;
	}
	
	return output;
}
*/

/* segment fault sur le output lors du strcat !
*/
char *represent(int a){
	char *c = malloc(100 * sizeof(char));
	
	if(a >= 0 && a <= 9)
		*c = '0' + a;
	else
		*c = 'a' - 10 + a;
		
	return c;
}

char *addition(int a, int b, int base){
	int tmp, n, current;
	char *output;
	
	n=0;
	tmp = a + b;
	
	output = malloc(100 * sizeof(char));
	output = "";
	
	while(tmp > 0)
	{
		current = tmp%base;
		printf("char : %c\n", *represent(current));
		//strcat(output, represent(current));
		tmp /= base;
		n++;
	}
	
	printf("\n");
	
	return output;
}

int main()
{
	
	printf("addition(1,1,2) = %d (10)\n", addition(1,1,2));
	printf("addition(2,3,3) = %d (11)\n", addition(2,2,3));
	printf("addition(13,7,8) = %d (22)\n", addition(13,7,8));
	printf("addition(133,67,8) = %d (222)\n", addition(13,7,8));
	printf("addition(2,2,16) = %d (4)\n", addition(2,2,16));
	printf("addition(1,15,16) = %d (10)\n", addition(1,15,16));
	printf("addition(15,15,16) = %d (1e)\n", addition(15,15,16));
	
	/*
	printf("addition(1,1,2) = %s (10)\n", addition(1,1,2));
	printf("addition(2,3,3) = %s (11)\n", addition(2,2,3));
	printf("addition(2,2,16) = %s (4)\n", addition(2,2,16));
	printf("addition(1,15,16) = %s (10)\n", addition(1,15,16));
	printf("addition(15,15,16) = %s (1e)\n", addition(15,15,16));
	*/
	
	return EXIT_SUCCESS;
}
