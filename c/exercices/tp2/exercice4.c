#include <stdio.h>

int main(void){
	int n=0;
	double e=1.0;
	
	do {
		e/=10.0;
		n++;
	} while(1.0+e!=1.0);
	
	printf("e = 10^-%d\n",n);
	
	return 0;
}
