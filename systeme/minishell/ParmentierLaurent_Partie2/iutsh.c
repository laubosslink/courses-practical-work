#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "ligne_commande.h"
#include "iutsh.h"


void affiche_prompt()
{
	/* Initialisation des variables */
	struct utsname infos;
	
	/* Affectation de la structure utsname (on aurai pu utiliser gethostname), mais je voulais étudier un autre chemin */
	if(uname(&infos) == -1)
		fprintf(stderr, "Problème avec uname");
	
	/* Affichage */
	printf("#iutsh# %s@%s:%s$ ", getenv("USER"), infos.nodename, getcwd(NULL, 0));
	fflush(stdout);
}


int lance_commande(int in, int out, char *com, char **argv)
{
	pid_t child;

	child = fork();

	if(child == -1)
		return -1;

	if(child == 0)
	{
		if(in != 0)
		{
			close(0);
			dup(in);
			close(in);
		}

		if(out != 1)
		{
			close(1);
			dup(out);
			close(out);
		}

		if(execvp(com, argv) == -1)
		{
			fprintf(stderr, "Problème avec la commande '%s'\n", com);
			exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);
	}  else 
	{
		if(in != 0)
		{
			close(in);
		}

		if(out != 1)
		{		
			close(out);
		}
	} 

	return child;
}

void execute_ligne_commande()
{
	/* Initialisation des variables */
	int flag=0, nb=0;
	int in=0;
	char ***cmd;
	int nCurrentCmd = 0;
	int pipefd[2];
	pid_t child;
	
	/* Attente qu'une commande soit entrée */
	cmd = ligne_commande(&flag, &nb);

	/* On parcour chaque commande */
	for(; nCurrentCmd<nb; nCurrentCmd++)
	{
		if(pipe(pipefd) != 0)
			fprintf(stderr, "Problème avec le pipe.\n");	

		/* Première ou dernier commande */
		if(nCurrentCmd == 0 || nCurrentCmd == nb-1)
		{
			if(nCurrentCmd == 0 && nb != 1)
			{
				child = lance_commande(0, pipefd[1], cmd[nCurrentCmd][0], cmd[nCurrentCmd]);
				in = pipefd[0];
			} else	
			{
				child = lance_commande(in, 1, cmd[nCurrentCmd][0], cmd[nCurrentCmd]);
			}	
		} else 
		{
			child = lance_commande(in, pipefd[1], cmd[nCurrentCmd][0], cmd[nCurrentCmd]);
			in = pipefd[0];
		}

		if(flag == 0)
		{		
			/* On attend que la commande se termine pour continuer */
			if(waitpid(child, NULL, 0) == -1)
				fprintf(stderr, "Probleme avec waitpid");
		}
		
		
	}
	
	libere(cmd);
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main()
{
	
	while(1)
	{
		affiche_prompt();
		execute_ligne_commande();
	}

	return EXIT_SUCCESS;
}
