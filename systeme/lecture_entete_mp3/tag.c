#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "tag.h"

int read_u8(int fd, u8 *val)
{
	if(read(fd, val, sizeof(u8)) == -1) return 0;

	return 1;
}

int read_u16(int fd, u16 *val)
{
	if(read(fd, val, sizeof(u16)) == -1) return 0;
	
	*val = *val>>8 | *val<<8;

	return 1;
}

int read_u32(int fd, u32 *val)
{
	u32 tmp;
	u32 mask;

	if(read(fd, val, sizeof(u32)) == -1) return 0;
	
	tmp = 0x00000000;	
	mask = 0x00FFFF00;

	tmp = *val & mask;
	
	tmp = tmp>>8 | tmp<<8;
	
	*val = *val>>24 | *val<<24;
	
	*val += tmp;
	
	return 1;
}

u32 convert_size(u32 size)
{
	u32 output=0x00000000;
	
	/* Dernière rangé d'octet */
	output = (size & 0x0000007F) + ((size & 0x00000100)>>1);
	
	/* rangé d'octet 3 */
	output += ((size & 0x00007E00)>>1) + ((size & 0x00030000)>>2);
	
	/* rangé d'octet 2 */
	output += ((size & 0x007C0000)>>2) + ((size & 0x07000000)>>3);
	
	/* première rangé d'octet*/
	output += ((size & 0x78000000)>>3);
	
	return output;
}

char *read_string(int fd, char *to, int size, int encoding)
{
	int i=0, x=0;
	
	char *newTo;
	
	if(to == NULL) to = (char *) malloc(size);
	
	if(read(fd, to, size) == -1) return NULL;
	
	if(encoding == 1)
	{
		/* On vérifie qu'il y a le FF FE au début */
		if((unsigned char)to[0] == 0xFF && (unsigned char)to[1] == 0xFE)
		{
		
		/* Si c'est le cas, on prépare une adresse mémoire qui va contenir la nouvelle phrase en ASCII */
		newTo = (char*) malloc((size-2)/2);
		
			for(i=2, x=0; i<size; i+=2, x++)
			{
				newTo[x] = to[i];
			}
		
		/* On libère la mémoire utilisé par to */
		(void) free(to);
		
		/* On remplace l'adresse mémoire de to (unicode) par celle de newTo(ascii) */
		to = newTo;
		
		} else 
		{
			return NULL;
		}
	}
	
	/* Ajout à la fin de \0 pour respecter ASCII */
	strcat(to, "\0");
	
	return to;
}

int tag_read_id3_header(int fd, id3v2_header_t *header)
{
	read_string(fd, header->ID3, 3, 0); 
	
	/* Vérification de l'ID */
	if(strcmp(header->ID3, "ID3") != 0)
	{
		return -1;
	}
	
	read_u16(fd, &(header->version));
	
	/* Vérification de la version
	Suite à la lecture little endian on a 0x0300 et non 0x0003 */
	if(header->version > 0x0300) 
	{
		return -1;
	}
	
	read_u8(fd, &(header->flags));
	read_u32(fd, &(header->size));
	
	/* Conversion de la taille header, comme spécifié dans le TP */
	header->size = convert_size(header->size);
	
	return 0;
}

int tag_read_one_frame(int fd, id3v2_frame_t *frame)
{
	u8 encodage;

	/**
	* TALB = nom de l'album
	* TRCK = numéro de la piste
	*/
	
	read_string(fd, frame->id, 4, 0);
	frame->id[ID3V2_FRAME_ID_LENGTH] = '\0';

	read_u32(fd, &(frame->size));
	read_u16(fd, &(frame->flags));	
	read_u8(fd, &encodage);
	
	frame->text = read_string(fd, NULL, frame->size-1, (int)encodage);
	
	if(frame->text == NULL) return -1;
	
	/* Vérification du type de frame */
	if(frame->id[0] != 'T' || strcmp(frame->id, "TXXX") == 0){
		return -1;
	}
	
	return 0;
}

id3v2_frame_t *tag_get_frames(const char *file, int *frame_array_size)
{
	int fd, i;
	
	id3v2_frame_t *frames; 

	fd = open(file, O_RDONLY);
	
	if(fd == -1) return NULL;

	/* D'après le TP, on doit lire l'header dans cette fonction, mais c'est illogique, où la stocker !? car on retourne un tableau de id3v2_frame_t alors que
	 * l'header doit se trouver dans la structure id3v2_header_t, or cette fonction ne la retourne pas, et elle ne se trouve pas dans les paramètres...
	 * C'est pourquoi on passe les 10 premiers octets, pour lire directement les frames */
	lseek(fd, 10, SEEK_SET);

	/* allocation d'un tableau */
	frames = (id3v2_frame_t*) malloc(sizeof(id3v2_frame_t) * (*frame_array_size));

	/* insertion des tags dans le tableau */
	for(i=0; i<*frame_array_size; i++)
	{
		/* Lorsqu'une frame n'est pas bonne, on arrête la boucle, et on réctifie frame_array_size (ce n'est pas pour rien que c'est un pointeur !?)*/
		if(tag_read_one_frame(fd, &frames[i]) != 0){
			*frame_array_size = i;
			break;
		}
	}

	/* Si la taille à été réajusté */
	frames = realloc(frames, sizeof(id3v2_frame_t) * (*frame_array_size));

	return frames;
}

void tag_free(id3v2_frame_t *frames, int frame_count)
{
	
	int i;
	
	for(i=0; i<frame_count; i++)
	{
		/* Aucune indication dans le tp, pas du tout guidé... après 1h de compréhension juste pour cette question abandon.. (20h au total pour faire ces 200lignes, c'est décourageant !) 
		 * Avec ce manque de "guidage" concernant le TP, on devient de tes mauvais codeur en C, remarque faite en cours, la plupart des étudiants, cherche des réponses toutes faites sur google...
		 * (par exemple pour passer de big endian à little endian). Au final, on devient incapable de coder en C. Plus de clarté, ou d'explications serait bien plus utiles... On avance plus vite,
		 * on comprend plus vite, et on devient moins découragé... Et on apprend à CODER !*/
		frames[i].id[0] = 0;
		frames[i].id[1] = 0;
		frames[i].id[2] = 0;
		frames[i].id[3] = 0;
		
		frames[i].size = 0;
		frames[i].flags = 0;
		free(frames[i].text);
	}
	
}


