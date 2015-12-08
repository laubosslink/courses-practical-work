#include <stdio.h>
#include <stdlib.h>

int main(){
	int a,b,c,d;

	printf("a:");
	scanf("%d", &a);
	printf("b:");
	scanf("%d", &b);
	printf("c:");
	scanf("%d", &c);
	printf("d:");
	scanf("%d", &d);

	if(!(!(a==1 && b == 1) || (c == 1 && d==0)))
	{
			printf("true\n");
	} else
	{
			printf("false\n");
	}

	return EXIT_SUCCESS;
}
