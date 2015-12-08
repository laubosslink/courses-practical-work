#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "tag.h"

id3v2_header_t enTete; 
id3v2_frame_t *frames;
int frameSize;

int main(int argc, char* argv[])
{
	/* Le file descriptor */
	int fd;

	/* Indice utilisé pour des boucles */
	int i;

	if(argc < 1) return EXIT_FAILURE;

	fd = open(argv[1], O_RDONLY);

	if(fd == -1) return EXIT_FAILURE;
	
	/* Lecture de l'entête*/
	if(tag_read_id3_header(fd, &enTete) == -1) return EXIT_FAILURE;
	
	printf("Informations de l'entête :\n\
ID : %s \n\
Version : %hd \n\
Flags : %d \n\
Taille : %d \n\n"
	, 
	enTete.ID3, 
	enTete.version, 
	enTete.flags, 
	enTete.size);
	
	/* Lecture d'une frame */
	/*
	if(tag_read_one_frame(fd, &frame) == -1) return EXIT_FAILURE;

	printf("Informations de la frame : \n\
ID : %s\n\
Taille : %d\n\
Flags : %d\n\
Texte : %s\n\
", frame.id, frame.size, frame.flags, frame.text);
	*/
	
	/* Lecture de plusieurs frames : */
	frameSize = 20; /* En cherchant, mais sans pousser les recherches (http://fr.wikipedia.org/wiki/ID3) on voit qu'il y a 20 aines de frame jusqu'à la version ID3v2 */
	
	frames = tag_get_frames(argv[1], &frameSize);
	
	if(frames == NULL) return EXIT_FAILURE;

	for(i=0; i<frameSize; i++){
	printf("Informations de la frame %d : \n\
ID : %s\n\
Taille : %d\n\
Flags : %d\n\
Texte : %s\n\
\n", i, frames[i].id, frames[i].size, frames[i].flags, frames[i].text);
	}

	/* Libèration de la mémoire */
	tag_free(frames, frameSize); 

	return EXIT_SUCCESS;
}


