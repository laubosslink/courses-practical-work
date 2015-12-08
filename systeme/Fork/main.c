#include <unistd.h>
	#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

	int a = 5;
	int b = 5;

	pid_t firstPID, secondPID;

	firstPID = fork();

	/* Pour ne pas créer de fils de fils */
	if(firstPID != 0)
	{
		secondPID = fork();
	}

	printf("%d\n", firstPID);

	/* PERE */
	if(firstPID != 0 && secondPID != 0)
	{
		a+=5;

		(void) sleep(5);

		printf("\n\Père (%d) (PP:%d):\n", getpid(), getppid());
		printf("a -> %d\n", a);
		printf("b -> %d\n", b);

		while(wait() != -1);
		//while(waitpid(-1, NULL, WNOHANG));

		printf("FIN PERE\n\n");


	} else if(firstPID != 0 || secondPID != 0) /* Fils premier niveau */
	{
		b+=5;

		(void) sleep(15);

		printf("\n\nFils (%d) (PP:%d)\n", getpid(), getppid());
		printf("a -> %d\n", a);
		printf("b -> %d\n", b);
		printf("FIN FILS\n\n");
	} else /* Fils de Fils */
	{
		b+=10;

		(void) sleep(20);

		printf("\n\nFils de FILS (%d) (PP:%d)\n", getpid(), getppid());
		printf("a -> %d\n", a);
		printf("b -> %d\n", b);
		printf("FIN FILS de FILS\n\n");
	}

	return EXIT_SUCCESS;
}
