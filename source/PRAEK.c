/*
 * PAEKS.c
 *
 *  Created on: 2021-09-28
 * 
 *      Author: kir
 *
 * 		Algorithms of PRAEKS scheme.
 * 
 * */
 
#include "PRAEK.h"


//====KeyGen & ReKeyGen Algorithm of PRAEK scheme====

int PRAEK_keygen_Receiver(element_t G1_pkR1, element_t G1_pkR2 , element_t G1_pkR3, 
		element_t Zr_skR1, element_t Zr_skR2, element_t Zr_skR3, element_t Zr_skR4) {
	
	keygen( G1_pkR1 ,  Zr_skR1 ) ;
	keygen( G1_pkR2 ,  Zr_skR2 ) ;
	keygen( G1_pkR3 ,  Zr_skR3 ) ;
	
	element_init_Zr( Zr_skR4 , pairing);
	element_random( Zr_skR4 );
	
	return 0;
}

int PRAEK_keygen_Sender(element_t G1_pkS, element_t Zr_skS){
	
	keygen(G1_pkS,  Zr_skS);
	
	return 0;
	}

int PRAEK_Re_keygen(char* displayMsg, element_t Zr_rk, element_t G1_pkSender, element_t Zr_skR1, element_t Zr_skR2, 
			element_t Zr_skR3, element_t Zr_skR4, int isDisp){
	
	//sharing key
	element_t sharingK;
	element_init_G1(sharingK, pairing);
	element_pow_zn(sharingK, G1_pkSender, Zr_skR1);
	if(isDisp){
		printString(displayMsg, "", 0);
		print_element("Re-keygen: sharingK \n", sharingK);
	}
	
	//H1(shrK)
	element_t Zr_denominator;
	PRAEK_Hash_1_FromG1_ToZr(Zr_denominator, sharingK, pairing);
	element_mul_zn(Zr_denominator, Zr_skR2, Zr_denominator);
	element_add(Zr_denominator, Zr_denominator, Zr_skR3);
	if(isDisp){
		print_element("Re-keygen: Zr_denominator \n", Zr_denominator);
	}
	
	//rk
	element_init_Zr(Zr_rk, pairing);
	element_div(Zr_rk, Zr_skR4, Zr_denominator);
	if(isDisp){
		print_element("Zr_skR4:\n", Zr_skR4);
		print_element("Re-encryption key: \n", Zr_rk);
	}
	 
	return 0;	
}

//====Encrypt & Re-Enc algorithm of PRAEK scheme====
unsigned char* PRAEK_encrypt(char* displayMsg, char *msg, element_t pk_R1, element_t pk_R2, element_t pk_R3, 
			element_t sk_Sender, int isDisp){
	//C1 = (pk_R2^{H(pk_r1^sk_Sender , w)} * pk_R3)^r
	//C2 = g^r
	
	unsigned char * ustr_C1_C2_C3_C4_pkSender = malloc(len1 * 5);
	 
	 // sharing key
	element_t sharingK;
	element_init_G1(sharingK, pairing);
	element_pow_zn(sharingK, pk_R1, sk_Sender);
	
	//H(shrK, w)
	element_t Zr_hw;
	PRAEK_Hash_FromG1timeschar_ToZr(Zr_hw, sharingK, msg, pairing);
	
	
	//H(shrK)
	element_t Zr_hk;
	PRAEK_Hash_1_FromG1_ToZr(Zr_hk, sharingK, pairing);
	
	//Randomly choose r from Z_p^*
	element_t Zr_r;
	Random_Zr(Zr_r, pairing);
	
	//C1
	element_t G1_C1;
	element_init_G1(G1_C1, pairing);
	
	element_pow_zn(G1_C1, pk_R2, Zr_hw);
	element_mul(G1_C1, G1_C1, pk_R3);
	element_pow_zn(G1_C1, G1_C1, Zr_r);
	
	//C2
	element_t G1_C2;
	element_init_G1(G1_C2, pairing);
	element_pow_zn(G1_C2, generator, Zr_r);
	
	//Randomly choose r2 from Z_p^*
	element_random(Zr_r);
	
	//C3
	element_t G1_C3;
	element_init_G1(G1_C3, pairing);
	
	element_pow_zn(G1_C3, pk_R2, Zr_hk);
	element_mul(G1_C3, G1_C3, pk_R3);
	element_pow_zn(G1_C3, G1_C3, Zr_r);
	
	//C4
	element_t G1_hw;
	PRAEK_Hash_2_FromChar_ToElement(G1_hw, msg, GROUPTYPE_G1);
	element_t G1_C4;
	element_init_G1(G1_C4, pairing);
	element_pow_zn(G1_C4, G1_hw, Zr_r);
	
	//C1||C2||C3||C4: Trans G1 type to unsigned char type
	element_to_bytes(ustr_C1_C2_C3_C4_pkSender, G1_C1);
	element_to_bytes(ustr_C1_C2_C3_C4_pkSender + len1, G1_C2);
	element_to_bytes(ustr_C1_C2_C3_C4_pkSender + len1*2, G1_C3);
	element_to_bytes(ustr_C1_C2_C3_C4_pkSender + len1*3, G1_C4);
	
	//C1||C2||C3||C4||pkSender
	element_t pk_Sender;
	element_init_G1(pk_Sender, pairing);
	element_pow_zn(pk_Sender, generator, sk_Sender);
	element_to_bytes(ustr_C1_C2_C3_C4_pkSender + len1 * 4, pk_Sender);
	
	if(isDisp){
		printUnsignedChar(displayMsg, ustr_C1_C2_C3_C4_pkSender, len1);
		printUnsignedChar("", ustr_C1_C2_C3_C4_pkSender + len1, len1);
		printUnsignedChar("", ustr_C1_C2_C3_C4_pkSender + len1*2, len1);
		printUnsignedChar("", ustr_C1_C2_C3_C4_pkSender + len1*3, len1);
		print_element("hash_msg: \n", Zr_hw);
	}
	
	return ustr_C1_C2_C3_C4_pkSender;  
 }
 
 unsigned char * PRAEK_Re_Enc(char* displayMsg, unsigned char* ustr_C1_C2_C3_C4_C5, 
			element_t Zr_rk, int isDisp){
	 
	 element_t G1_C3;
	 element_init_G1(G1_C3, pairing);
	 element_from_bytes(G1_C3, ustr_C1_C2_C3_C4_C5 + len1 * 2);
	 
	 element_t G1_C5;
	 element_init_G1(G1_C5, pairing);
	 element_pow_zn(G1_C5, G1_C3, Zr_rk);
	 
	 element_to_bytes(ustr_C1_C2_C3_C4_C5 + len1 * 4, G1_C5);
	 
	 if(isDisp){
	printUnsignedChar(displayMsg, ustr_C1_C2_C3_C4_C5, len1);
	printUnsignedChar("", ustr_C1_C2_C3_C4_C5 + len1, len1);
	printUnsignedChar("", ustr_C1_C2_C3_C4_C5 + len1*2, len1);
	printUnsignedChar("", ustr_C1_C2_C3_C4_C5 + len1*3, len1);
	printUnsignedChar("", ustr_C1_C2_C3_C4_C5 + len1*4, len1);
	//print_element("G1_C3\n", G1_C3);
	//print_element("G1_C5\n", G1_C5);
	}
	 
	 return ustr_C1_C2_C3_C4_C5;
 }

//====Trapdoor & Re-Trapdoor algorithm of PRAEK scheme====
unsigned char* PRAEK_trapdoor(char* displayMsg, char* msg, element_t pk_Sender, element_t sk_R1, 
			element_t sk_R2, element_t sk_R3, int isDisp){
	
	unsigned char * ustr_Tw1_Tw2_pkSender = malloc(len1 * 2 + len1);
				
	// H(shrK, w)
	element_t sharingK;
	element_init_G1(sharingK, pairing);
	element_pow_zn(sharingK, pk_Sender, sk_R1);
	
	element_t Zr_hw;
	PRAEK_Hash_FromG1timeschar_ToZr(Zr_hw, sharingK, msg, pairing);
	
	// Randomly choose r from Z_p^*
	element_t Zr_r;
	Random_Zr(Zr_r, pairing);
	
	// sk_R2 * H(pk_s ^ sk_R1, w') + sk_R3
	element_t Zr_expofC1;
	element_init_Zr(Zr_expofC1, pairing);
	element_mul(Zr_expofC1, sk_R2, Zr_hw);
	element_add(Zr_expofC1, Zr_expofC1, sk_R3);
	element_invert(Zr_expofC1, Zr_expofC1);
	
	// {r / sk_R2 * H(pk_s ^ sk_R1, w') + sk_R3}
	element_mul_zn(Zr_expofC1, Zr_r, Zr_expofC1);
	
	// Tw1 = g^{r / sk_R2 * H(pk_s ^ sk_R1, w') + sk_R3}
	element_t G1_Tw1;
	element_init_G1(G1_Tw1, pairing);
	element_pow_zn(G1_Tw1, generator, Zr_expofC1);	
	
	//print_element("sk_R3 in PRAEK_trapdoor: ", sk_R3);
	
	//Tw2 = g^ r
	element_t G1_Tw2;
	element_init_G1(G1_Tw2, pairing);
	element_pow_zn(G1_Tw2, generator, Zr_r);
	
	//Tw1||Tw2: Trans G1 type to unsigned char type
	element_to_bytes(ustr_Tw1_Tw2_pkSender, G1_Tw1);
	element_to_bytes(ustr_Tw1_Tw2_pkSender + len1, G1_Tw2);
	
	//Tw1||Tw2||pkSender
	element_to_bytes(ustr_Tw1_Tw2_pkSender + len1 * 2, pk_Sender);
	
	if(isDisp){
		printUnsignedChar(displayMsg, ustr_Tw1_Tw2_pkSender, len1);
		printUnsignedChar("", ustr_Tw1_Tw2_pkSender + len1, len1);
		printUnsignedChar("pkSender: ", ustr_Tw1_Tw2_pkSender + len1 *2, 30);
		print_element("hash_msg: \n", Zr_hw);
	}
	
	return ustr_Tw1_Tw2_pkSender;  
}

unsigned char * PRAEK_Re_trapdoor(char * displayMsg, unsigned char * ustr_Tw1_Tw2, char* msg, 
			element_t Zr_skR4, int isDisp){
	
	//Randomly select r from Zp^*
	element_t Zr_r;
	Random_Zr(Zr_r, pairing);
	
	//Tw2 & print Hash value
	element_t G1_Tw2;
	PRAEK_Hash_2_FromChar_ToElement(G1_Tw2, msg, GROUPTYPE_G1);
		
	//print Hash value
	if(isDisp){
		printUnsignedChar(displayMsg, ustr_Tw1_Tw2, len1);
		printUnsignedChar("", ustr_Tw1_Tw2 + len1, len1);
		print_element("hash_msg: \n", G1_Tw2);
	}
		
	//Tw2
	element_pow_zn(G1_Tw2, G1_Tw2, Zr_r);
	
	//Tw1
	element_t G1_Tw1;
	element_init_G1(G1_Tw1, pairing);
	element_mul_zn(Zr_r, Zr_r, Zr_skR4);
	element_pow_zn(G1_Tw1, generator, Zr_r);
	
	//Tw1||Tw2: Trans G1 type to unsigned char type
	element_to_bytes(ustr_Tw1_Tw2, G1_Tw1);
	element_to_bytes(ustr_Tw1_Tw2 + len1, G1_Tw2);
	
	return ustr_Tw1_Tw2;
}

//====Test & Re-Test algorithm of PRAEK scheme====
int PRAEK_test(char* displayMsg, unsigned char* ustr_Tw1_Tw2, unsigned char* ustr_C1_C2, int isDisp){
	 
	//Read G1_Tw1, G1_Tw2 from unsigned char type input
	element_t G1_Tw1, G1_Tw2;
	element_init_G1(G1_Tw1, pairing);
	element_init_G1(G1_Tw2, pairing);
	element_from_bytes(G1_Tw1, ustr_Tw1_Tw2);
	element_from_bytes(G1_Tw2, ustr_Tw1_Tw2 + len1);
	
	//Read G1_C1, G1_C2 from unsigned char type input
	element_t G1_C1, G1_C2;
	element_init_G1(G1_C1, pairing);
	element_init_G1(G1_C2, pairing);
	element_from_bytes(G1_C1, ustr_C1_C2);
	element_from_bytes(G1_C2, ustr_C1_C2 + len1);
	
	//Pairing: e(C1, Tw1) and e(C2, Tw2)
	element_t GT_C1_e_Tw1, GT_C2_e_Tw2;
	element_init_GT(GT_C1_e_Tw1, pairing);
	element_init_GT(GT_C2_e_Tw2, pairing);
	element_pairing(GT_C1_e_Tw1, G1_C1, G1_Tw1);
	element_pairing(GT_C2_e_Tw2, G1_C2, G1_Tw2);
	
	//print_element("GT_C1_e_Tw1 is: \n", GT_C1_e_Tw1);
	//print_element("GT_C2_e_Tw2 is: \n", GT_C2_e_Tw2);
	
	int cmp = element_cmp(GT_C1_e_Tw1, GT_C2_e_Tw2);
	if (isDisp){
		if (!cmp)
			printString(displayMsg, "1", NODISPLAY) ;
		else
			printString(displayMsg, "0", NODISPLAY) ;		
	} //endif(idDisp)
	
	 return (1-cmp);
}
 
int PRAEK_Re_test(char* displayMsg, unsigned char* ustr_Tw1_Tw2, unsigned char* ustr_C1_C2_C3_C4_C5, int isDisp){
	  
	int testResult = PRAEK_test(displayMsg, ustr_Tw1_Tw2, ustr_C1_C2_C3_C4_C5 + len1 * 3, isDisp);
	  
	return testResult;
}
	
	
	