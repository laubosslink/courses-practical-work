;*********************************
; @file :  FIR_asm.asm
; @brief : Algorithme d'un filtre FIR - assembleur sans optimisation (utilisation de LDW)
; @author : 
; last modification : 
;*********************************

	.global		_FIR_asm		; Permet de rendre le label accessible par d'autre fichier (idem extern en "C")


_FIR_asm:						; Preceder un label par "_" permet de le rendre accessible depuis un fichier "C"

   	mv 		a6,b0				; recuperation du nombre d'iterations dans b0
	zero		a2
LOOP:
	ldw		.d1		*a4++,a0	; chargement d'un coef a dans a0
	nop				4		; temps de deplacement memoire

	ldw		.d2		*b4++,a1	; chargement d'un echantillon x dans a1
	nop				4

	mpy		.m1		a0,a1,a3	; multiplication de la parte basse
	nop				1

	mpyh		.m1		a0,a1,a5	; multiplication de la partie haute
	nop				1

	add		.l1		a2,a3,a2	; a2 += a3 (ajout partie basse)
	add		.l1		a2,a5,a2	; a2 += a5 (ajout partie haute)

	sub		.s2		b0,2,b0		; decremente de 2 car on charge deux echantillons (ldw, charge 32 bits)

	[b0] b 		.s1		LOOP

	nop				5		; l'instruction b prend 6 cycles d'horloges

	mv		.d1		a2,a4
	 
	b		.s2		b3		; Branchement sur l'adresse de retour, sauvee dans B3 avant de rentrer dans la fonction
	shr		.s1		a4,15,a4	; y_dg += (coeff[i]*x_dg[i])   >>15; (decalage de 15)
	nop				4
