#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void swap(int *a, int *b){
	int c;

	c = *b;
	*b = *a;
	*a = c;
}

/* p = n/2 */
long c(int n, int p){
	if(p > n)
		swap(&p, &n);

	if(p == 0 || p == n)
		return 1;

	return c(n-1, p-1) + c(n-1, p);
}

void exercice5()
{
	int n, p;
	long coef;
	time_t debut, fin;

	for(n=0; n<40; n++){
		for(p=1; p<=n/2; p++){

			/*n=p*2;*/

			time(&debut);
			coef = c(n, p);
			time(&fin);

			if(difftime(fin, debut) > 1){
				printf("LONG: c(%d,%d) = %ld\n", n, p, coef);
				fflush(stdout);
			} /*else {
				printf("COURT: c(%d,%d) = %ld\n", n, p, coef);
				fflush(stdout);
			}*/
		}
	}

}
