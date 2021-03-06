/*********************************
 @file :  USL.c
 @brief : USL.c (User Support Library) est une librairie utilisateur pour la trame de TP sur DSP TMS320C6713B
 @author : 
 last modification : 
*********************************/

	/*********************
	 *** FONCTION : G�n�ration d'�chantillons d'une sinuso�de d'amplitude "0,5" � 6KHz	
	 *** @brief :  	Il ne faut appeler SineGen qu'une fois toutes les 20,8us (48KHz) 	
	 *** 			afin de g�n�rer une sinuso�de � 6KHz. Calcul effectu� avec des FLOTTANTS
	 ***    
	 *** @return SineSample : �chantillon de sinus (entier sur 16bits)	 								
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
	 *** FONCTION : G�n�ration d'�chantillons d'une sinuso�de d'amplitude "0,5" � 6KHz	
	 *** @brief :  	Il ne faut appeler SineGen qu'une fois toutes les 20,8us (48KHz) 	
	 *** 			afin de g�n�rer une sinuso�de � 6KHz. Calcul effectu� avec des ENTIERS
	 ***    
	 *** @return SineSample : �chantillon de sinus (entier sur 16bits)	 								
	 *********************/
	short SineGenQ15(void){ 
	static 	short	y[3] = {0, 0, 0x7FFF * 0.353934};	/*** 0,353934 peut �tre cod� en Q15  ***/
	static	short	a = 0x7FFF * 0.707107;				/*** 1.414215 ne peut pas �tre cod� au format Q15,e n revanche 1.414215/2 = 0.707107 peut l'�tre  ***/
			short 	SineSample;

		y[0] = (a*y[1])>>15 - y[2];
		y[2] = y[1];
		y[1] = y[0];

		SineSample = (short) (0x7FFF * y[0]) * 2;

	return SineSample;
	}  


	/*********************
	 *** FONCTION : Raffraichissement d'un tableau avec des �chantillons de sinus (pour EDMA)	
	 ***    
	 *** @param ptBuffer : 	pointeur sur le tableau � raffraichir
	 *** @param bufferSize : nombre d'�chantillons de sinus (voies gauche et droite) � �crire dans le tableau	 								
	 *********************/
	void BlockGen( short *ptBuffer, short bufferSize){
	short signal, i = 0;

		while( i != bufferSize )
			{
			 signal = SineGen();		/*** Calcul d'un �chantillon de sinus ***/
			 ptBuffer[i++] = signal;    
			 ptBuffer[i++] = signal;    
			}
	}


	/*********************
	 *** FONCTION : D�calage des �chantillons avant filtrage (viellissement de donn�es)	
	 ***    
	 *** @param x_dg : 		pointeur sur le tableau d'�chantillons
	 *** @param nbCoeff :  	taille du tableau d'�chantillons 						
	 *********************/
	void DecBuffer(short *x_dg, short nbCoeff){
		int i;
		
		for(i=nbCoeff-1; i>=1; i--)
		{
			x_dg[i] = x_dg[i-1];
		}
	}


	/*********************
	 *** FONCTION : Algorithme de filtrage d'un filtre FIR (forme DIRECTE)	
	 *** @brief : calculs sur entiers sign�s sur 16bits
	 ***    
	 *** @param coeff : 	pointeur sur le tableau de coefficients
	 *** @param x_dg : 		pointeur sur le tableau d'�chantillons 
	 *** @param nbCoeff :  	taille des tableaux (ordre du filtre + 1)							
	 *********************/
	short FIR_C(short *coeff, short *x_dg, short nbCoeff){

	short y_dg=0;
	int i;

	for(i=0; i<nbCoeff; i++){
		y_dg += (coeff[i]*x_dg[i])>>15;
	} 
							
	return y_dg;
	}


	/*********************
	 *** FONCTION : Copie d'un tableau de BufferSize �l�ments (adres source)
	 ***    
	 *** @param source :  		pointeur sur le tableau source � copier
	 *** @param destination :  	pointeur sur le tableau de destination � �crire 
	 *** @param BufferSize :    nombre d'�l�ments � copier						
	 *********************/
	void CopyBuffer(short *source, short *destination, short BufferSize){
		int i;
		for(i=0; i<BufferSize; i++){
			destination[i] = source[i];
		}
	}


