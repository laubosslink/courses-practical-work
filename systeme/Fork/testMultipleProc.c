#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * Développement d'un systeme de multiple processus 
 * Il semble que ceci existe dans la doc officiel avec des groupID (équivalent à ceci)
 * en plus performant, et dans les normes...
 * 
 * Bref, ceci aura servit d'exemple, et d'essai pour mieux comprendre la gestion
 * de plusieurs processus.
 */

int NUMBERPROC = 10;
	
int isFather(pid_t *childs)
{
	int i=0;
	
	for(;i<NUMBERPROC;i++)
	{
		if(childs[i] == 0)
		{
			return 1;
		}
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	pid_t *childs = (pid_t *) malloc(sizeof(pid_t) * NUMBERPROC);
	
	int i=0;
	
	/* Initialisation de NUMBERPROC fils */
	for(;i<NUMBERPROC;i++)
	{
		childs[i] = fork();

		/* Chaque fils crée, continue son chemin, et ne rentre pas dans la boucle en créant un fils de fils */
		if(childs[i] == 0)
		{
			break;
		}
		
		if(childs[i] == -1)
		{
			printf("PROBLEME");
		}
	}
	
	
	if(isFather(childs) == 0)
	{
		int i=0;
		/* wait(-1); ne semble pas fonctionner, d'où cette solution */
		for(;i<NUMBERPROC; i++)
		{
			wait(childs[i]);
		}
		
		printf("Père : %d\n", getpid());
	} else 
	{
		if(childs[0] == 0)
		{
			sleep(3);
			printf("FILS 1 (%d, %d)\n", getpid(), getppid());
		} else if(childs[1] == 0)
		{
			sleep(1);
			printf("FILS 2 (%d, %d)\n", getpid(), getppid());
		} else if(childs[2] == 0)
		{
			sleep(10);
			printf("FILS 3 (%d, %d)\n", getpid(), getppid());
		} else if(childs[3] == 0)
		{
			printf("FILS 4 (%d, %d)\n", getpid(), getppid());
		} else if(childs[4] == 0)
		{
			printf("FILS 5 (%d, %d)\n", getpid(), getppid());
		} else
		{
			sleep(20);
			printf("FILS X\n");
		}
		
	}
	
	return EXIT_SUCCESS;
}		

