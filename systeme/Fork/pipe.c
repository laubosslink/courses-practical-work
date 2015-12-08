#include <unistd.h>
	#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int pipefd[2];
	char *myChar = (char *) malloc(sizeof(char) * 10);
	unsigned int numb;
	char buf;
	pid_t fils1, fils2;
	
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	fils1 = fork();
	
	if(fils1 != 0)
		fils2 = fork();
		
	/* Père */
	if(fils1 != 0 && fils2 != 0)
	{
		printf("Veuillez entrer un nombre : ");
		(void) scanf("%d", &numb);
		//numb = 100;
		//printf("%s\n", myChar);
		
		close(pipefd[0]);
		write(pipefd[1], &numb, sizeof(numb));
		
		sleep(5);
		
		numb = 15;
		
		write(pipefd[1], &numb, sizeof(int));
		
		close(pipefd[1]);
		//wait(NULL);
		
	} else /* Fils */
	{
		// Premier fils, on affiche négativement
		if(fils1 == 0)
		{
			close(pipefd[1]);
			
			//while(read(pipefd[0], &numb, 1) > 0)
				//write(STDOUT_FILENO, &numb, sizeof(numb));
				
			//write(STDOUT_FILENO, "\n", 1);
			
			read(pipefd[0], &numb, sizeof(numb));
			
			printf("%d\n", numb);
			
			
			read(pipefd[0], &numb, sizeof(numb));
			
			printf("%d\n", numb);
			
			close(pipefd[0]);
			
		}
	}
	
	return EXIT_SUCCESS;
}
