/*********************************
 @file :  ex3.c
 @brief : Filtre numérique FIR par polling (ou scutation)
 @author : 
 last modification : 
*********************************/

/* Includes files */
#include "ex3cfg.h"      // header file généré par CCS à la compilation (utilisation DSP/BIOS) 
#include "USL.h"


/* Déclaration variables configuration codec TLV320AIC23 */
DSK6713_AIC23_CodecHandle hAIC23;

DSK6713_AIC23_Config confAIC23 = { 
	    0x0017,  	/* 0 DSK6713_AIC23_LEFTINVOl  left line input channel volume 	*/ 
	    0x0017,  	/* 1 DSK6713_AIC23_RIGHTINVOl Right line input channel volume 	*/
	    0x01f9,  	/* 2 DSK6713_AIC23_LEFTHPVOl  left channel headphone volume 	*/  
	    0x01f9,  	/* 3 DSK6713_AIC23_RIGHTHPVOl Right channel headphone volume 	*/ 
	    0x0011,  	/* 4 DSK6713_AIC23_ANAPATH    Analog audio path control 		*/      
	    0x0000,  	/* 5 DSK6713_AIC23_DIGPATH    Digital audio path control 		*/     
	    0x0000,  	/* 6 DSK6713_AIC23_POWERDOWN  Power down control 				*/             
	    0x0043,  	/* 7 DSK6713_AIC23_DIGIF      Digital audio interface format 	*/ 
	    0x0081,  	/* 8 DSK6713_AIC23_SAMPLERATE Sample rate control		 		*/            
	    0x0001   	/* 9 DSK6713_AIC23_DIGACT     Digital interface activation 	*/   
	};


/**************************
 *** MAIN FUNCTION - Programm entry point
 ***************************/
void main(void){
short   a[NB_COEFF] = {A_COEFF};
short   x_d[NB_COEFF];
short   x_g[NB_COEFF];
Uint32	x0_d, x0_g, y_d, y_g; 

	/* Initialisation librairie BSL - config CPLD routage maquette DSK6713 */
	DSK6713_init();
		
	
	/* Initialisation switch DSK6713 */

	DSK6713_DIP_init();
		
	/* Initialisation et configuration Codec Audio TLV320AIC23 */

	hAIC23 = DSK6713_AIC23_openCodec(0, &confAIC23);
	
	while(1){

		/* ATTENDRE réception de deux echantillons depuis l'AIC23 (voies gauche et droite) */
		while(!DSK6713_AIC23_read(hAIC23, &x0_d));
		while(!DSK6713_AIC23_read(hAIC23, &x0_g));
		

		/* Algorithme de filtrage */		

		DecBuffer(x_d, NB_COEFF);
		DecBuffer(x_g, NB_COEFF);

		x_d[0] = x0_d;
		x_g[0] = x0_g;

		y_d = FIR_C(a, x_d, NB_COEFF);
		y_g = FIR_C(a, x_g, NB_COEFF);
				
			
		/* ATTENDRE transmission de deux echantillons vers l'AIC23 */	
		while(!DSK6713_AIC23_write(hAIC23, y_d));
		while(!DSK6713_AIC23_write(hAIC23, y_g));
	}    
}
