/*********************************
 @file :  USL.h (User Support Library header)
 @brief : fichier d'en-t�te travaillant avec USL.c pour la trame de TP sur DSP TMS320C6713B
 @author : 
 last modification : 
*********************************/
#ifndef   __USL_HEADER__
#define   __USL_HEADER__

	/* Includes files dependencies */
	#include <dsk6713.h>			/*** Macros et prototypes de BSL (inclu CSL.h) ***/
	#include <dsk6713_aic23.h>		/*** Macros et prototypes de BSL pour la gestion du TLV320AIC23 ***/
	#include <csl_irq.h>			/*** Macros et prototypes de CSL pour la gestion des Interruptions ***/
	#include <csl_edma.h>			/*** Macros et prototypes de CSL pour la gestion de l'EDMA ***/

	/*** Macros � usage g�n�ral ***/
	#define DROITE  1
	#define GAUCHE  0

	/*** Macros filtrage num�rique FIR ***/
	#define         NB_COEFF    	16	
	#define         A_COEFF   		-1608,   4238,   2798,   2647,   2851,   3097,   3292,   3405,   3405,  3292,   3097,   2851,   2647,   2798,   4238,  -1608

	/*** Macros gestion EDMA ***/
	#define         BUFFERSIZE      56
	#define         PING            0
	#define         PONG            1
	#define 		TCC             14
	#define         TCC_T           14 
	#define         TCC_R           15                     
	#define         DXR1            0x01900004      /*** Adresse du registre de transmission DXR1 du McBSP1 ***/
	#define         DRR1            0x01900000      /*** Adresse du registre de r�ception DRR1 du McBSP1 ***/
	
	/*** Macros gestion CACHE et Buffer Circulaire ***/
	//#define         BUFFERSIZE      128		// taille multiple d'une ligne en cache L2
	#define         AMR_BK_SIZE     4		// taille block en octect (registre AMR adressage circulaire)


	/*** D�claration fonctions publiques (d�finitions dans USL.c) ***/

		/*********************
		 *** FONCTION : G�n�ration d'�chantillons d'une sinuso�de d'amplitude "0,5" � 6KHz	
		 *** @brief :  	Il ne faut appeler SineGen qu'une fois toutes les 20,8us (48KHz) 	
		 *** 			afin de g�n�rer une sinuso�de � 6KHz. Calcul effectu� avec des FLOTTANTS
		 ***    
		 *** @return : �chantillon de sinus (entier sur 16bits)	 								
		 *********************/
		extern short SineGen(void);

		/*********************
		 *** FONCTION : G�n�ration d'�chantillons d'une sinuso�de d'amplitude "0,5" � 6KHz	
		 *** @brief :  	Il ne faut appeler SineGen qu'une fois toutes les 20,8us (48KHz) 	
		 *** 			afin de g�n�rer une sinuso�de � 6KHz. Calcul effectu� avec des ENTIERS
		 ***    
		 *** @return : �chantillon de sinus (entier sur 16bits)	 								
		 *********************/
		extern short SineGenQ15(void);

		/*********************
		 *** FONCTION : Raffraichissement d'un tableau avec des �chantillons de sinus (pour EDMA)	
		 ***    
		 *** @param ptBuffer : 	pointeur sur le tableau � raffraichir
		 *** @param bufferSize : nombre d'�chantillons de sinus (voies gauche et droite) � �crire dans le tableau	 								
		 *********************/
		void BlockGen( short *ptBuffer, short bufferSize);

		/*********************
		 *** FONCTION : D�calage des �chantillons avant filtrage (viellissement de donn�es)	
		 ***    
		 *** @param x_dg : 		pointeur sur le tableau d'�chantillons
		 *** @param nbCoeff :  	taille du tableau d'�chantillons 						
		 *********************/
		extern void DecBuffer(short *ptx_dg, short nbCoeff);

		/*********************
		 *** FONCTION : Algorithme de filtrage d'un filtre FIR (forme DIRECTE)
		 *** @brief : calculs sur entiers sign�s sur 16bits	
		 ***    
		 *** @param coeff : 	pointeur sur le tableau de coefficients
		 *** @param x_dg : 		pointeur sur le tableau d'�chantillons 
		 *** @param nbCoeff :  	taille des tableaux (ordre du filtre + 1)							
		 *********************/
		extern short FIR_C(short *pta, short *ptx_dg, short nbCoeff);

		/*********************
		 *** FONCTION : Algorithme de filtrage d'un filtre FIR (forme DIRECTE)
		 *** @brief : 	Algo en assembleur sans optimisation avec instruction LDH (puis LDW)
		 ***			Registre B7 configur� en mode d'adressage circulaire	
		 ***    
		 *** @param pta : 	pointeur sur le tableau de coefficients
		 *** @param ptx_dg : 		pointeur sur le tableau d'�chantillons 
		 *** @param nbCoeff :  	taille des tableaux (ordre du filtre + 1)							
		 *********************/
		extern short FIR_asm(short *pta, short *ptx_dg, short nbCoeff);

		/*********************
		 *** FONCTION : Algorithme de filtrage d'un filtre FIR (forme DIRECTE)
		 *** @brief : 	Algo en assembleur lin�aire avec LDW
		 ***    
		 *** @param pta : 	pointeur sur le tableau de coefficients
		 *** @param ptx_dg : 		pointeur sur le tableau d'�chantillons 
		 *** @param nbCoeff :  	taille des tableaux (ordre du filtre + 1)							
		 *********************/
		extern short FIR_sa(short *pta, short *ptx_dg, short nbCoeff); 

		/*********************
		 *** FONCTION : Algorithme de filtrage d'un filtre FIR (forme DIRECTE)
		 *** @brief : 	Algo en assembleur avec pipelining softaware d'instructions et LDW
		 ***    
		 *** @param pta : 	pointeur sur le tableau de coefficients
		 *** @param ptx_dg : 		pointeur sur le tableau d'�chantillons 
		 *** @param nbCoeff :  	taille des tableaux (ordre du filtre + 1)							
		 *********************/		 	
		extern short FIR_asmPipe(short *pta, short *ptx_dg, short nbCoeff); 

		/*********************
		 *** FONCTION : Copie d'un tableau de BufferSize �l�ments (adres source)
		 ***    
		 *** @param source :  		pointeur sur le tableau source � copier
		 *** @param destination :  	pointeur sur le tableau de destination � �crire 
		 *** @param BufferSize :    nombre d'�l�ments � copier						
		 *********************/
		extern void	CopyBuffer(short *source, short *destination, short BufferSize);

#endif
