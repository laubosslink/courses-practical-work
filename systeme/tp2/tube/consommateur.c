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

#include <string.h>

int main()
{
	char alreadyRead[26];

	// Initialisation de la memoire de la pile
	memset(alreadyRead, 0, sizeof(char) * 26);

	char buff;

	int fd = open("/tmp/producteur", O_RDONLY);

	do
	{
		read(fd, &buff, sizeof(char));

		printf("%d\n", (char)buff);

		// 65 == "A"
		if(alreadyRead[((int) buff-65)] == buff) // Deuxieme lecture d'un caractere
			break; // On peut donc s'arrêter
		else // Premiere lecture d'un caractere
			alreadyRead[((int)buff-65)] = buff;
	} while(1);

	return 0;
}
