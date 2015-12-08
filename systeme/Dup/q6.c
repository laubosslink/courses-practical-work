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
	pid_t lsProc;
	pid_t cutProc;
	pid_t sortProc;
	
	/* Si on est le père, création d'un nouveau processus fils */
	if(newProc != 0)
		lsProc = fork();
	else
		lsProc = -1;
		
	// prob... lsProc va démarér cutProc...
	if(newProc != 0)
		cutProc = fork();
	else
		cutProc = -1;
		
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
		char *args[] = {"grep", "-e", "^-.w.*$", NULL};
		execvp(args[0], args);
		
	} else if(lsProc == 0) /* Fils lsProc */
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
		
	} else /* Pere */
	{
		/* Permet d'attendre que tout les fils soient terminés */
		wait(-1);
	}
	
	return EXIT_SUCCESS;
}
