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
	
	if(newProc == 0)
	{
		
		close(pipefd[0]);
		
		sendMessage("Ouverture du fichier.");
		int fd = open(argv[1], O_RDONLY);
		if(fd == -1)
			return EXIT_FAILURE;
		
		close(0);
		dup(fd);
		close(fd);
		
		buff = getchar();
		
		while(buff != '\0' && buff != EOF)
		{
			write(pipefd[1], &buff, sizeof(int));
			buff = getchar();
		}
		
		close(pipefd[1]);
		
	} else
	{
		wait(newProc);
		
		close(pipefd[1]);
		
		sendMessage("Message : ");
		while(read(pipefd[0], &buff, sizeof(int) > 0))
		{
			printf("%c", (char) buff);
		}
		
		printf("\n");
		
		sendMessage("Fin père.");
		
		close(pipefd[0]);
	}
	
	return EXIT_SUCCESS;
}
