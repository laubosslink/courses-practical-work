#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

pid_t newProc(int second)
{
	pid_t proc = fork();
	
	if(proc == 0)
	{
		sleep(second*2);
		printf("fin fils %d !!\n", getpid());
		exit(0);
	}
	
	return proc;
}

int main(int argc, char *argv[])
{
	int i=0;
	
	printf("MAIN : %d \n", getpid());
	
	pid_t gpId = newProc(0);
	pid_t newFork;
	
	setpgid(gpId, getpid());
	
	for(;i<5;++i)
	{
		newFork = newProc(i);
		printf("fils : %d associé père %d\n", newFork, gpId);
		setpgid(newFork, gpId);
	}
	
	printf("GROUP ID : %d \n", gpId);
	
	/* '(int*) NULL' is important, could also specify 'int status' var. */
    while(wait((int*) NULL) != -1); /* wait all childs */

	printf("Fin père\n");
	
	return EXIT_SUCCESS;
}
