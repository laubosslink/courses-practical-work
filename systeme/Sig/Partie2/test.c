#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <sys/types.h>

int lance_commande(char *com, char **argv)
{
	int err;
	pid_t child;

	child = fork();

	if(child == -1)
		return -1;

	if(child == 0)
	{
		err = execvp(com, argv);

		if(err == -1)
			exit(EXIT_FAILURE);
		
		exit(EXIT_SUCCESS);
	}

	return child;
}

int main(int argc, char **argv)
{
	char **test = (char **) malloc(sizeof(char) * 2);
	test[0] = (char *) malloc(sizeof(char) * 2);
	test[0] = "ls";
	test[1] = NULL;
	
	printf("pid : %d\n", lance_commande(test[0], test));

	return EXIT_SUCCESS;
}
