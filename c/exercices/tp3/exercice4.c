#include <stdlib.h>
#include <stdio.h>

int pgcd_iteratif(int a, int b){
	int r;
	
	r = a%b;
	
	while(r > 0){
		a = b;
		b = r;
		r = a%b;
	}

	return b;
}

int pgcd(int a, int b){
	if(a%b > 0)
		return pgcd(b, a%b);
	return b;
}

void exercice4(){
	printf("pgcd(15, 5) = %d\n", pgcd_iteratif(15, 5));
	printf("pgcd(5, 15) = %d\n", pgcd_iteratif(5, 15));
	printf("pgcd(11, 17) = %d\n", pgcd_iteratif(11, 17));
	printf("pgcd(4, 12) = %d\n", pgcd_iteratif(4, 12));
	printf("pgcd(45741, 213456) = %d\n", pgcd_iteratif(45741, 213456));
	printf("pgcd(16, 9) = %d\n", pgcd_iteratif(16, 9));
	
	printf("\n");
	
	printf("pgcd(15, 5) = %d\n", pgcd(15, 5));
	printf("pgcd(5, 15) = %d\n", pgcd(5, 15));
	printf("pgcd(11, 17) = %d\n", pgcd(11, 17));
	printf("pgcd(4, 12) = %d\n", pgcd(4, 12));
	printf("pgcd(45741, 213456) = %d\n", pgcd(45741, 213456));
	printf("pgcd(16, 9) = %d\n", pgcd(16, 9));
}
