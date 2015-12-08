/*********************************
 @file :  ex1.c
 @brief : Génération d'un signal Sinusoïdal sans EDMA
 @author : 
 last modification : 
*********************************/

/* Includes files */
#include "ex1cfg.h"        // header file généré par CCS à la compilation (utilisation DSP/BIOS) 
#include "USL.h"

/* Déclaration variables configuration codec TLV320AIC23 */
DSK6713_AIC23_CodecHandle hAIC23;

DSK6713_AIC23_Config confAIC23 = { 
	    0x0017,  	/* 0 DSK6713_AIC23_LEFTINVOl  left line input channel volume 	*/ 
	    0x0017,  	/* 1 DSK6713_AIC23_RIGHTINVOl Right line input channel volume 	*/
	    0x01f9, 	/* 2 DSK6713_AIC23_LEFTHPVOl  left channel headphone volume 	*/  
	    0x01f9, 	/* 3 DSK6713_AIC23_RIGHTHPVOl Right channel headphone volume 	*/ 
	    0x0011, 	/* 4 DSK6713_AIC23_ANAPATH    Analog audio path control 		*/      
	    0x0000, 	/* 5 DSK6713_AIC23_DIGPATH    Digital audio path control 		*/     
	    0x0000, 	/* 6 DSK6713_AIC23_POWERDOWN  Power down control 				*/             
	    0x0043, 	/* 7 DSK6713_AIC23_DIGIF      Digital audio interface format 	*/ 
	    0x0081, 	/* 8 DSK6713_AIC23_SAMPLERATE Sample rate control		 		*/            
	    0x0001  	/* 9 DSK6713_AIC23_DIGACT     Digital interface activation 	*/   
	};

/* Déclaration fonctions privées */
void XINT1_HWI(void);

/* Gestion interruptions avec DSP/BIOS */
IRQ_Config IRQ_Config_XINT1 = {XINT1_HWI, 0x00000000, IRQ_CCMASK_DEFAULT, IRQ_IEMASK_DEFAULT};	// Attributs IRQ du McBSP1 transmission


/****************************
 *** ISR ou HWI : fonction d'interruption associée au McBSP1 en Transmission																
 *** @brief :	cette ISR est appelée à chaque fois que le registre de transmission du MCBSP1 est vide et toutes les 20,8us													
 *** 			Le codec audio TLV320AIC23 envoi deux échantillons par période d'échantillonnage (voies gauche et droite)
 ****************************/
void XINT1_HWI(void){
static  short voie = DROITE;  
static  short signal;

	/* gestion des voies (gauche et droite) */
	if(voie == DROITE)
	{		
		if(DSK6713_DIP_get(0))
		{
			signal = SineGen();
		} else 
		{
			signal = SineGenQ15();
		}
		voie = GAUCHE;
	} else {
		voie = DROITE;
	}

	/* Transmission échantillon au codec TLV320AIC23 */		
	DSK6713_AIC23_write(hAIC23, signal);
}
                                                       

/**************************
 *** MAIN FUNCTION - Programm entry point
 ***************************/
void main(void){

	/* Initialisation librairie BSL - config CPLD routage maquette DSK6713 */
	DSK6713_init();

	/* Configuration manuelle IT avec DSP/BIOS (.cdb) */
	/* IMPORTANT : cocher "Use dispatcher" via interface GUI (avant appel IRQ_Config) */
	//IRQ_map(IRQ_EVT_XINT1, 12);						// Routage source IRQ (McBSP1 transmission) vers vecteur n°12
	//IRQ_config(IRQ_EVT_XINT1, &IRQ_Config_XINT1);	// Configuration vecteur d'IT

	/* Initialisation switch DSK6713 */
	DSK6713_DIP_init();

	/* Initialisation et configuration Codec Audio TLV320AIC23 */
	hAIC23 = DSK6713_AIC23_openCodec(0, &confAIC23);

	/* Démasquage Interruption MCBSP1 en transmission côté CPU (registre IER du CPU) */

	//IER
	IRQ_enable(IRQ_EVT_XINT1);

	/* Démasquage global des IT côté CPU (registre IER champ GIE) */

	// GIE
	IRQ_globalEnable();

}
