#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

double trinome(double x)
{
	return x * x * x + 2 * x * x - 4 * x - 3;
}

double zeroDicho(double a, double b){
	double i=(a+b)/2;
	
	if((float)a == (float)b)
		return i;
	
	if(trinome(i) < 0)
		return zeroDicho(i, b);
	else
		return zeroDicho(a, i);
}

void exercice6(){
	printf("f(x)=0; quand x~=%f;\n", zeroDicho(0, 100));
}
