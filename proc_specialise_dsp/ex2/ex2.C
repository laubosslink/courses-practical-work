/*********************************
 @file :  ex2.c
 @brief : G�n�ration d'un signal Sinuso�dal avec EDMA
 @author : 
 last modification : 
*********************************/

/* Includes files */
#include "ex2cfg.h"		  // header file g�n�r� par CCS � la compilation (utilisation DSP/BIOS) 
#include "USL.h"


/* D�claration variables configuration codec TLV320AIC23 */
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


/* D�claration variables gestion EDMA */
short buffer[ BUFFERSIZE ];

EDMA_Handle hEdmaReload;       	// Pointeur sur table de Reload 

EDMA_Handle hEdma14;           	// Pointeur sur configuration canal n�14 EDMA
	
EDMA_Config confEDMA = {		// Configuration canal n�14 EDMA (6 champs de 32bits)

			EDMA_OPT_RMK(	
				EDMA_OPT_PRI_LOW,			/* Priorit� basse pour les transferts de l'EDMA													*/
				EDMA_OPT_ESIZE_16BIT, 		/* Taille de chaque �l�ment																		*/
				EDMA_OPT_2DS_NO,			/* Source � 1 dimension																			*/
				EDMA_OPT_SUM_INC,			/* Incr�mentation de l'adresse source � chaque event re�u										*/
				EDMA_OPT_2DD_NO,			/* Destination � 1 dimension																	*/
				EDMA_OPT_DUM_NONE,			/* Pas d'op�ration sur l'adresse de destination : DXR1 (registre de transmission du McBSP1)		*/
				EDMA_OPT_TCINT_YES,			/* Validation globale de l'IT de l'EDMA															*/
				EDMA_OPT_TCC_OF(14),		/* Initialisation de TCC, num�ro du canal utilis� 												*/	
				EDMA_OPT_LINK_YES,			/* Utilisation d'une table de Reload															*/
				EDMA_OPT_FS_NO				/* Synchronisation sur �l�ment et non sur trame													*/
				     ),	
				     				
			EDMA_SRC_OF(buffer),   			/* Adresse SOURCE : adresse du tableau ou sont stock�s les �chantillons du signal � transmettre	*/
					
			EDMA_CNT_OF(BUFFERSIZE),		/* Nombre d'�l�ments � transf�rer, avec : M-1=0 (16 Msb) et N=56 (16 Lsb), cf. doc CCS			*/

			EDMA_DST_OF(DXR1),				/* Adresse de DESTINATION : DXR1 = 0x01900004 (registre de transmission du McBSP1)				*/

			EDMA_IDX_OF(PING),					/* Pas d'indexage 																				*/

			EDMA_RLD_OF(0)  				/* Adresse de la table de RELOAD utilis�e, champ modifi� dans "Edma_init"						*/
			};



/*********************
 *** FONCTION : Configuration du canal 14 de l'EDMA
 *** @brief :  	transferts � 1 dimension, allocation automatique de la table de reload, 	
 *** 			pointeur source incr�ment�, pointeur destination inchang�, validation interruption
 ***			canal n�14, validation event canal n�14, synchro sur �l�ment ...
 ***    								
 *********************/
void EDMA_Init(void){

	/* Autorisation d'utilisation du canal n�14 et masquage event XEVT1 - EDMA_open */
	hEdma14 = EDMA_open(EDMA_CHA_XEVT1, EDMA_OPEN_ENABLE);

	/* Allocation table de Reload, 1 parmi 69. Retourne l'adresse (handle ou pointeur) d'une table libre  */
	hEdmaReload = EDMA_allocTable(-1);			

	/* MAJ structure "confEDMA" champ "EDMA_RLF_OF(0)" */
	confEDMA.rld = ( confEDMA.rld & 0xffff0000 ) | ( EDMA_RLD_RMK(0, hEdmaReload) );

	/* Configuration canal n�14 de l'EDMA - EDMA_config */

	EDMA_config(hEdma14,&confEDMA);

	/* Configuration table de reload "hEdmaReload" de l'EDMA - EDMA_config */	

	EDMA_config(hEdmaReload,&confEDMA);

	/* D�masqage event XEVT1 de l'EDMA (canal n�14). Ecriture dans le registre EER - EDMA_enableChannel */	

	EDMA_enableChannel(hEdma14);
}                               


/****************************
 *** ISR ou HWI : fonction d'interruption li�e � l'EDMA																	
 *** @brief :	L'EDMA envoi une IRQ au CPU lorsque le transfert de BUFFERSIZE �l�ments 											
 *** 			du tableau "buffer"	vers le McBSP1 est fini (DXR1 register)
 ****************************/
void EDMA_HWI(void){

	/* RAZ du flag d'interruption c�t� EDMA (registre CIPR bit n�14) - EDMA_intClear */	
	EDMA_intClear(TCC);

	/* MAJ du tableau d'�chantillons utilis� par l'EDMA (via SWI dans la suite du TP) */
	//BlockGen(buffer, BUFFERSIZE);
	SWI_post(&SWI_ex2);
}

void BlockGen_SWI(void)
{

	BlockGen(buffer, BUFFERSIZE);
}


/**************************
 *** MAIN FUNCTION - Programm entry point
 ***************************/
void main(void){
	

	/* MAJ du tableau d'�chantillons utilis� par l'EDMA */
	BlockGen(buffer, BUFFERSIZE);

	/* Initialisation librairie BSL - config CPLD routage maquette DSK6713 */

	DSK6713_init();			

	/* Configuration canal n�14 de l'EDMA */

	//	EDMA_Init();
	//CSL_Init();
	
	/* Initialisation et configuration Codec Audio TLV320AIC23 */

	hAIC23 = DSK6713_AIC23_openCodec(0, &confAIC23);

	/* D�masquage Interruption EDMA c�t� CPU (registre IER du CPU) */

	IRQ_enable(IRQ_EVT_EDMAINT);	

	/* D�masquage Interruption Canal n�14 c�t� EDMA (registre CIER champ TCC de l'EDMA) */

	EDMA_intEnable(TCC);

	/* D�masquage global des IT c�t� CPU (registre IER champ GIE) */

	IRQ_globalEnable();
}

