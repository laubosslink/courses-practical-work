#include <stdio.h>
#include <stdlib.h>

// limite a n=7
short fact_short(short n)
{
	short i, output;

	output=1;

	for(i=1; i<=n; i++)
	{
		output *= i;
	}

	return output;
}

// limite a n=16
int fact_int(int n)
{
	int i, output;

	output=1;

	for(i=1; i<=n; i++)
	{
		output *= i;
	}

	return output;
}

// limite a n=20
long long fact_long(long long n)
{
	long long i;
	long long output;

	output=1;

	for(i=1; i<=n; i++)
	{
		output *= i;
	}

	return output;
}

int main()
{
	unsigned int n;
	
	printf("Please enter n:");
	
	scanf("%ud", &n);
	
	printf("short fact(%d): %hd\n", n, fact_short(n));
	
	printf("short fact(%d): %d\n", n, fact_int(n));
	
	printf("short fact(%d): %lld\n", n, fact_long(n));
	
	return EXIT_SUCCESS;
}
