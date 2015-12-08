#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void sendMessage(const char *message)
{
	printf("%s\n", message);
}

int main(int argc, char *argv[])
{
	int buff;
	int pipefd[2];
	
	sendMessage("Création d'un pipe.");
	if(pipe(pipefd) != 0)
		return EXIT_FAILURE;
	
	pid_t newProc = fork();
	
	/* Fils */
	if(newProc == 0)
	{
		/* Attente de la fin du processus père */
		wait(getppid());
		
		/* Fermeture de l'écriture du pipe */
		close(pipefd[1]);
		/* Fermeture de la lecture standard */
		close(0);
		
		/* Duplique de la lecture du pipe dans la lecture standard */
		dup(pipefd[0]);
		/* Fermeture de la lecture du pipe */
		close(pipefd[0]);
		
		/* Execution de grep sur la lecture standard (cad lecture du pipe) */
		char *args[] = {"grep", "-e", "^-.w.*$", NULL}; // Recouvrement oblifatoire pour bon fonctionnement (cad NULL obligatoire)
		execvp(args[0], args);
		
	} else /* Pere */
	{
		/* Fermeture lecture du pipe */
		close(pipefd[0]);
		/* Fermeture écriture standard */
		close(1);
		
		/* Duplique de l'écriture du pipe dans l'écriture standard */
		dup(pipefd[1]);
		/* Fermeture de l'écriture du pipe */
		close(pipefd[1]);
		
		/* Execution de la commande ls -l, écrie dans l'écritude standard (cad écriture pipe) */
		char *args[] = {"ls", "-l"};
		execvp(args[0], args);
	}
	
	return EXIT_SUCCESS;
}
