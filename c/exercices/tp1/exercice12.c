#include <stdio.h>
#include <stdlib.h>

// a)
int min(int v1, int v2){
	return (v1 < v2)? v1 : v2;
}

int main(){
	int e1, e2, e3, e4;
	
	// b) 
	printf("min(1, 2) : %d\n", min(1, 2));
	
	printf("min(4, 2) : %d\n", min(4, 2));
	
	printf("min(1, 1) : %d\n", min(1, 1));
	
	// c)
	printf("Veillez entrer 4 entiers\n");
	printf("\ne1:");
	scanf("%d", &e1);
	printf("\ne2:");
	scanf("%d", &e2);
	printf("\ne3:");
	scanf("%d", &e3);
	printf("\ne4:");
	scanf("%d", &e4);
	
	if(min(e1, e2) <= min(e3, e4))
	{
		printf("min: %d\n", min(e1, e2));
	} else 
	{
		printf("min: %d\n", min(e3, e4));
	}
	
	// d) on conclue que la réalisation précédente est plus facile a utiliser, et prend moins de ligne de code
	if(e1 < e2)
	{
		if(e1 < e3)
		{
			if(e1 < e4)
			{
				printf("min: %d", e1);
			} else
			{
				printf("min: %d", e4);
			}
		} else
		{
			if(e3 < e4)
			{
				printf("min: %d", e3);
			} else
			{
				printf("min: %d", e4);
			}
		}
	} else
	{
		if(e2 < e3)
		{
			if(e2 < e4)
			{
				printf("min: %d", e2);
			} else
			{
				printf("min: %d", e4);
			}
		} else
		{
			if(e3 < e4)
			{
				printf("min: %d", e3);
			} else
			{
				printf("min: %d", e4);
			}
		}
	}

	printf("\n");

	return EXIT_SUCCESS;
}
