/*********************************
 @file :  	ex4.c
 @brief : 	Filtre num�rique FIR : sans optimisation, optimisation grossi�re, 
 			assembleur lin�aire puis Pipelining Software
 @author : 	
 last modification : 
*********************************/

/* Includes files */
#include "ex4cfg.h"          // header file g�n�r� par CCS � la compilation (utilisation DSP/BIOS) 
#include "USL.h" 


/* D�claration variables configuration codec TLV320AIC23 */
DSK6713_AIC23_CodecHandle hAIC23;

DSK6713_AIC23_Config confAIC23 = { 
	    0x0017,  /* 0 DSK6713_AIC23_LEFTINVOl  left line input channel volume 	*/ 
	    0x0017,  /* 1 DSK6713_AIC23_RIGHTINVOl Right line input channel volume 	*/
	    0x01f9,  /* 2 DSK6713_AIC23_LEFTHPVOl  left channel headphone volume 	*/  
	    0x01f9,  /* 3 DSK6713_AIC23_RIGHTHPVOl Right channel headphone volume 	*/ 
	    0x0011,  /* 4 DSK6713_AIC23_ANAPATH    Analog audio path control 		*/      
	    0x0000,  /* 5 DSK6713_AIC23_DIGPATH    Digital audio path control 		*/     
	    0x0000,  /* 6 DSK6713_AIC23_POWERDOWN  Power down control 				*/             
	    0x0043,  /* 7 DSK6713_AIC23_DIGIF      Digital audio interface format 	*/ 
	    0x0081,  /* 8 DSK6713_AIC23_SAMPLERATE Sample rate control		 		*/            
	    0x0001   /* 9 DSK6713_AIC23_DIGACT     Digital interface activation 	*/   
	};

/* Ressources partag�es par les ISR */
Uint32	x0_d, x0_g, y_d, y_g;


/****************************
 *** ISR ou HWI : fonction d'interruption associ�e au McBSP1 en R�ception																
 *** @brief :	cette ISR est appel�e � chaque fois que le MCBSP1 re�oit une donn�e depuis l'AIC23														
 *** 			Le codec audio TLV320AIC23 envoi deux �chantillons par p�riode d'�chantillonnage (voies gauche et droite)
 ****************************/
void RINT1_HWI(void){
static  char voie = DROITE;  

	/* R�ception des �chantillons depuis le codec TLV320AIC23 */	
	if(voie == DROITE){

		voie = GAUCHE;
		DSK6713_AIC23_read(hAIC23, &x0_d);				
	}
	else{
	 
		voie = DROITE;
		DSK6713_AIC23_read(hAIC23, &x0_g);
	}
}


/****************************
 *** ISR ou HWI : fonction d'interruption associ�e au McBSP1 en Transmission																
 *** @brief :	cette ISR est appel�e � chaque fois que le codec AIC23 est pr�t � recevoir une nouvelle donn�e														
 *** 			Le codec audio TLV320AIC23 re�oit deux �chantillons par p�riode d'�chantillonnage (voies gauche et droite)
 ****************************/
void XINT1_HWI(void){
static  char voie = DROITE;  

	/* Envoi des �chantillons au codec TLV320AIC23 */
	if(voie == DROITE){

		voie = GAUCHE;
		DSK6713_AIC23_write(hAIC23, y_d);				
	}
	else{
	 
		voie = DROITE;
		DSK6713_AIC23_write(hAIC23, y_g);
		SWI_post(&SWI_ex4);
	}	
}


/****************************
 *** SWI : 		fonction d'interruption logicielle li�e � l'ISR "XINT1_HWI" 																
 *** @brief :	fonction synchronis�e sur l'ISR associ�e au MCBSP1 en transmission											
 *** 			A chaque fois que deux �chantillons sont r�ceptionn�s (voies gauche et droite)
 ***			cette fonction est appel�e afin d'impl�menter l'UN des diff�rents algorithmes de filtrage
 ****************************/
void AlgoFIR_SWI(void){	
short   		a[NB_COEFF] = {A_COEFF};
static short   	x_d[NB_COEFF];
static short   	x_g[NB_COEFF];
	
		/* Raffraichissement du tableau d'�chantillons */
		DecBuffer(x_d, NB_COEFF);
		DecBuffer(x_g, NB_COEFF);
		
		x_d[0] = x0_d;
		x_g[0] = x0_g;

		/* Filtre FIR - Langage C */
		if( !DSK6713_DIP_get(0) ){
			STS_set(&STS_C,CLK_gethtime());
				y_d = FIR_C(a, x_d, NB_COEFF);
			STS_delta(&STS_C,CLK_gethtime());

			y_g = FIR_C(a, x_g, NB_COEFF);

		/* Filtre FIR - Assembleur sans optimisation avec LDW */						
		}else if( !DSK6713_DIP_get(1) ){
			STS_set(&STS_asm,CLK_gethtime());
			y_d = FIR_asm(a, x_d, NB_COEFF);
			STS_delta(&STS_asm,CLK_gethtime());

			y_g = FIR_asm(a, x_g, NB_COEFF);

		/* Filtre FIR - Assembleur Lin�aire avec LDW */
		}else if( !DSK6713_DIP_get(2) ){
			STS_set(&STS_sa,CLK_gethtime());
			y_d = FIR_sa(a, x_d, NB_COEFF);
			STS_delta(&STS_sa,CLK_gethtime());

			y_g = FIR_sa(a, x_g, NB_COEFF);

		/* Filtre FIR - Assembleur avec pipelining software et LDW */
		}else if( !DSK6713_DIP_get(3) ){
			
			// *** � compl�ter *** !

		/* Filtre passe tout par d�faut */
		}else {
			y_d = x0_d;
			y_g = x0_g;
		}										
}


/**************************
 *** MAIN FUNCTION - Programm entry point
 ***************************/
void main(void){

	/* Initialisation librairie BSL - config CPLD routage maquette DSK6713 */

	DSK6713_init();

	/* Initialisation switch DSK6713 */

	DSK6713_DIP_init();

	/* Initialisation et configuration Codec Audio TLV320AIC23 */

	hAIC23 = DSK6713_AIC23_openCodec(0, &confAIC23);

	/* D�masquage Interruption MCBSP1 en r�ception c�t� CPU (registre IER du CPU) */

	IRQ_enable(IRQ_EVT_XINT1);

	/* D�masquage Interruption MCBSP1 en transmission c�t� CPU (registre IER du CPU) */

	IRQ_enable(IRQ_EVT_RINT1);
		
	/* D�masquage global des IT c�t� CPU (registre IER champ GIE) */

	IRQ_globalEnable();

}
