/** 
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin 
 * F-14050 Caen Cedex 
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */ 

/**
 * @author El Himdi Yasmine <yasmine.elhimdi@ecole.ensicaen.fr> 
 * @author Parmentier Laurent <laurent.parmentier@ecole.ensicaen.fr> 
 */

#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>

int main(int argc, char *argv[])
{
	srand(time(NULL));

	mkfifo("/tmp/producteur", 0666);
	int fd = open("/tmp/producteur", O_CREAT | O_WRONLY);

	const char base = 'A';
	char buff;

	while(1)
	{
		buff = base + rand()%26;
		write(fd, &buff, sizeof(char));
		buff++;
		sleep(1);
	}

	return 0;
}
