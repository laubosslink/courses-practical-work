#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t newProc = fork();
	
	if(newProc == 0)
	{
		char *args[] = {"ls", "-l", NULL};
		
		execvp(args[0], args);
		
		perror("");
	} else 
	{
		wait();
		printf("Je suis ton père\n");
	}
	
	return EXIT_SUCCESS;
}
