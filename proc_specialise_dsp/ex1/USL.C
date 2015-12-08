/*********************************
 @file :  USL.c
 @brief : USL.c (User Support Library) est une librairie utilisateur pour la trame de TP sur DSP TMS320C6713B
 @author : 
 last modification : 
*********************************/

	/*********************
	 *** FONCTION : Génération d'échantillons d'une sinusoïde d'amplitude "0,5" à 6KHz	
	 *** @brief :  	Il ne faut appeler SineGen qu'une fois toutes les 20,8us (48KHz) 	
	 *** 			afin de générer une sinusoîde à 6KHz. Calcul effectué avec des FLOTTANTS
	 ***    
	 *** @return SineSample : échantillon de sinus (entier sur 16bits)	 								
	 *********************/
	short SineGen(void){
	static 	float 	y[3] = {0, 0, 0.353934};
	static 	float 	a = 1.414215;
			short 	SineSample;

		y[0] = a*y[1] - y[2];
		y[2] = y[1];
		y[1] = y[0];

		SineSample = (short) (0x7FFF * y[0]);

	return SineSample;
	} 


	/*********************
	 *** FONCTION : Génération d'échantillons d'une sinusoïde d'amplitude "0,5" à 6KHz	
	 *** @brief :  	Il ne faut appeler SineGen qu'une fois toutes les 20,8us (48KHz) 	
	 *** 			afin de générer une sinusoîde à 6KHz. Calcul effectué avec des ENTIERS
	 ***    
	 *** @return SineSample : échantillon de sinus (entier sur 16bits)	 								
	 *********************/
	short SineGenQ15(void){ 
	static 	short	y[3] = {0, 0, 0x7FFF * 0.353934};	/*** 0,353934 peut être codé en Q15  ***/
	static	short	a = 0x7FFF * 0.707107;				/*** 1.414215 ne peut pas être codé au format Q15,e n revanche 1.414215/2 = 0.707107 peut l'être  ***/
			short 	SineSample;

		y[0] = (a*y[1])>>15 - y[2];
		y[2] = y[1];
		y[1] = y[0];

		SineSample = (short) (0x7FFF * y[0]) * 2;

	return SineSample;
	}  


	/*********************
	 *** FONCTION : Raffraichissement d'un tableau avec des échantillons de sinus (pour EDMA)	
	 ***    
	 *** @param ptBuffer : 	pointeur sur le tableau à raffraichir
	 *** @param bufferSize : nombre d'échantillons de sinus (voies gauche et droite) à écrire dans le tableau	 								
	 *********************/
	void BlockGen( short *ptBuffer, short bufferSize){
	short signal, i = 0;

		while( i != bufferSize )
			{
			 signal = SineGen();		/*** Calcul d'un échantillon de sinus ***/
			 ptBuffer[i++] = signal;    
			 ptBuffer[i++] = signal;    
			}
	}


	/*********************
	 *** FONCTION : Décalage des échantillons avant filtrage (viellissement de données)	
	 ***    
	 *** @param x_dg : 		pointeur sur le tableau d'échantillons
	 *** @param nbCoeff :  	taille du tableau d'échantillons 						
	 *********************/
	void DecBuffer(short *x_dg, short nbCoeff){

		// *** à compléter *** !	
	}


	/*********************
	 *** FONCTION : Algorithme de filtrage d'un filtre FIR (forme DIRECTE)	
	 *** @brief : calculs sur entiers signés sur 16bits
	 ***    
	 *** @param coeff : 	pointeur sur le tableau de coefficients
	 *** @param x_dg : 		pointeur sur le tableau d'échantillons 
	 *** @param nbCoeff :  	taille des tableaux (ordre du filtre + 1)							
	 *********************/
	short FIR_C(short *coeff, short *x_dg, short nbCoeff){

			// *** à compléter *** !
							
	return 	0;
	}


	/*********************
	 *** FONCTION : Copie d'un tableau de BufferSize éléments (adres source)
	 ***    
	 *** @param source :  		pointeur sur le tableau source à copier
	 *** @param destination :  	pointeur sur le tableau de destination à écrire 
	 *** @param BufferSize :    nombre d'éléments à copier						
	 *********************/
	void CopyBuffer(short *source, short *destination, short BufferSize){

		// *** à compléter *** !
	}


