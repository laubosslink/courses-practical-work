;*********************************
; @file :  FIR_asmPipe.asm
; @brief : Algorithme d'un filtre FIR - assembleur avec optimisation (pipelining software - utilisation de LDW)
; @author : 
; last modification : 
;*********************************

	.global		_FIR_asmPipe		; Permet de rendre le label accessible par d'autre fichier (idem extern en "C")

	
_FIR_asmPipe:

	mv A6,B0
	zero A2
	zero B2

c1			LDW 	.D1 	*A4++,A7
	|| 		LDW 	.D2 	*B4++,B7

c2			LDW 	.D1 	*A4++,A7
	|| 		LDW 	.D2 	*B4++,B7
	|| [B0]	SUB 	.S2 	B0,2,B0

c3			LDW 	.D1 	*A4++,A7
	|| 		LDW 	.D2 	*B4++,B7
	|| [B0]	SUB 	.S2 	B0,2,B0
	|| [B0]	B 		.S1 	LOOP

c4			LDW 	.D1 	*A4++,A7
	|| 		LDW 	.D2 	*B5++,B7
	|| [B0] SUB 	.S2 	B0,2,B0
	|| [B0] B 		.S1 	LOOP

c5			LDW 	.D1 	*A4++,A7
	|| 		LDW 	.D2 	*B4++,B7
	|| [B0]	SUB 	.S2 	B0,2,B0
	|| [B0]	B 		.S1 	LOOP

c6			LDW 	.D1 	*A4++,A7
	|| 		LDW 	.D2 	*B4++,B7
	|| [B0]	SUB 	.S2 	B0,2,B0
	|| [B0]	B 		.S1 	LOOP
	|| MPYH 		.M1 	A7,B7,A5
	|| MPY 			.M2 	A7,B7,B5

c7			LDW 	.D1 	*A4++,A7
	|| 		LDW 	.D2 	*B4++,B7
	|| [B0]	SUB 	.S2 	B0,2,B0
	|| [B0]	B 		.S1 	LOOP
	|| 		MPYH 	.M1 	A7,B7,A5
	|| 		MPY 	.M2 	A7,B7,B5

LOOP:		LDW 	.D1 	*A4++,A7
	||		LDW 	.D2 	*B4++,B7
	|| [B0]	SUB 	.S2 	B0,2,B0
	|| [B0]	B 		.S1 	LOOP
	|| 		MPYH 	.M1 	A7,B7,A5
	||		MPY 	.M2 	A7,B7,B5
	||		ADD 	.L1 	A2,A5,A2
	||		ADD 	.L2 	B2,B5,B2
	
			ADD A2,B2,A4

			B		.s2		b3			; Branchement sur l'adresse de retour, sauvée dans B3 avant de rentrer dans la fonction
			SHT		.s1		a4,15,a4	; y_dg += (coeff[i]*x_dg[i])   >>15; (decalage de 15)
			NOP				4
