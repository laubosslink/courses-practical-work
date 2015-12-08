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
#include <stdlib.h>

#include <sys/signal.h>

int i;

void repondeur (int s)
{
	if (s == SIGTERM)
	{
		i++;
	}
}

int main()
{
	i=0;

	signal( SIGTERM, repondeur);
	while(1)
	{
		printf("Toc Toc %d\n", i);
		sleep(2);
	}
	return 0;
}
