#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <sys/types.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)


void infanticide()
{
	printf("Infanticide.\n");
	fflush(stdout);

	pid_t child = fork();	

	if(child == 0)
	{
		printf("Création fils (%d)\n", getpid());
		fflush(stdout);
		sleep(10);
		printf("Term fils (%d)\n", getpid());
		fflush(stdout);
	} else 
	{
		printf("Père (%d) -> fils (%d)\n", getpid(), child);
		fflush(stdout);		
		printf("PAN FILS (%d)\n", child);
		fflush(stdout);
		kill(child, 9);
	}
}

void agonieChildTerm(int sig)
{
	printf("Argh, je meurs...\n");
	fflush(stdout);
	
	exit(sig);
}

void agonie()
{
	printf("Agonie.\n");
	fflush(stdout);
	int status;

	struct sigaction sa;
	
	sa.sa_flags = SA_NOMASK;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &agonieChildTerm;
	/*sa.sa_sigaction = agonieChildTerm;*/
	
	pid_t child = fork();

	if(child == 0)
	{
		
		if(sigaction(SIGTERM, &sa, NULL) == -1)
			handle_error("sigaction"); 
			
		sleep(10);
		printf("Le fils ne doit pas pouvoir arriver ici...\n");
		/*fflush(stdout);*/
	} else
	{
		sleep(1);
		printf("Pan !\n");
		fflush(stdout);
		
		kill(child, SIGTERM);
		wait(&status);
		
		if(WIFSIGNALED(status))
		{
			printf("Niak, niak niak j'ai eu %d (signal : %d) !\n", child, WTERMSIG(status));
			fflush(stdout);
		} else if(WIFEXITED(status))
		{
			printf("Mmmh %d (signal : %d)...\n", child, WEXITSTATUS(status));
			fflush(stdout);
		} else
		{
			printf("Pas eu %d\n", child);
			fflush(stdout);
		}
	}
}

volatile sig_atomic_t life;

void resistanceChildSig(int sig)
{

	if(life > 1)
	{
		life -= 1;
		printf("Aie\n");
	} else {
		printf("Argh, je meurs...\n");
		exit(sig);
	}
}

void resistance()
{
	printf("Debut resistance.\n");
	int status;

	struct sigaction sa;
	
	sa.sa_flags = SA_NOMASK;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &resistanceChildSig;
	/*sa.sa_sigaction = agonieChildTerm;*/
	
	pid_t child = fork();

	if(child == 0)
	{
		
		/* nombre de vie entre 1 et 10 */
		srand48(time(NULL));
		life = (drand48()*9);
		
		printf("Fils de pid %d a %d vie(s)\n", getpid(), life);

		if(sigaction(SIGUSR1, &sa, NULL) == -1)
			handle_error("sigaction"); 

		while(1){}

	} else
	{
		sleep(1);

		(void) waitpid(child, &status, WNOHANG);

		while(!WIFEXITED(status)){

			printf("Pan !\n");
			fflush(stdout);
			
			kill(child, SIGUSR1);

			(void) waitpid(child, &status, WNOHANG);

			sleep(1);
		}

		wait(&status);		


		if(WIFEXITED(status))
		{
			printf("Niak, niak niak j'ai eu %d (signal : %d) !\n", child, WEXITSTATUS(status));
			fflush(stdout);
		} else
		{
			printf("Pas eu %d\n", child);
			fflush(stdout);
		}
	}
}

void duel()
{
	printf("duel.\n");
	fflush(stdout);

printf("Debut resistance.\n");
	int status;

	struct sigaction sa;
	
	sa.sa_flags = SA_NOMASK;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &resistanceChildSig;
	/*sa.sa_sigaction = agonieChildTerm;*/
	
	pid_t child = fork();

	if(child == 0)
	{
		
		/* nombre de vie entre 1 et 10 */
		srand48(time(NULL));
		life = (drand48()*9);
		
		printf("Fils de pid %d a %d vie(s)\n", getpid(), life);

		if(sigaction(SIGUSR1, &sa, NULL) == -1)
			handle_error("sigaction"); 

		sleep(1);

		(void) waitpid(getppid(), &status, WNOHANG);

		while(!WIFEXITED(status)){

			printf("Fils -> Pan !\n");
	
			kill(getppid(), SIGUSR1);

			(void) waitpid(getppid(), &status, WNOHANG);

			sleep(1);
		}

		wait(&status);		


		if(WIFEXITED(status))
		{
			printf("Fils -> Niak, niak niak j'ai eu %d (signal : %d) !\n", child, WEXITSTATUS(status));
			fflush(stdout);
		} else
		{
			printf("Pas eu %d\n", child);
			fflush(stdout);
		}

	} else
	{

		/* nombre de vie entre 1 et 10 */
		srand48(time(NULL));
		life = (drand48()*9);
		
		printf("Pere de pid %d a %d vie(s)\n", getpid(), life);

		if(sigaction(SIGUSR1, &sa, NULL) == -1)
			handle_error("sigaction"); 

		(void) waitpid(child, &status, WNOHANG);

		while(!WIFEXITED(status)){

			printf("Pere -> Pan !\n");
	
			kill(child, SIGUSR1);

			(void) waitpid(child, &status, WNOHANG);

			sleep(1);
		}

		wait(&status);		


		if(WIFEXITED(status))
		{
			printf("Pere -> Niak, niak niak j'ai eu %d (signal : %d) !\n", child, WEXITSTATUS(status));
			fflush(stdout);
		} else
		{
			printf("Pas eu %d\n", child);
			fflush(stdout);
		}
	}
}



int main(int argc, char *argv[])
{
	if(argc == 1)
		printf("%s\n--ex1 : Infanticide\n--ex2 : Agonie\n--ex3 : Debut de resistance\n--ex4 : Duel\n", argv[0]);

	int n=1;

	for(; n<argc; n++)
	{
		if(strcmp(argv[n], "--ex1") == 0)
			infanticide();
		else if(strcmp(argv[n], "--ex2") == 0)
			agonie();
		else if(strcmp(argv[n], "--ex3") == 0)
			resistance();
		else if(strcmp(argv[n], "--ex4") == 0)
			duel();
			
	}

	return EXIT_SUCCESS;
}
