/*	
 * 	test.c
 * 	
 * 		Created on: 2017-2-22
 * 			Author: kir
 * 		Implement test algorithm in PAEKS scheme.
 * 		Input with the PAEKS ciphertext, trapdoor, and public key of the receiver.
 * 		Output 1 if the inputting ciphertext and ciphertext contain the same keyword.
 * 
 * */
 
 #include "PAEKS_main.h"
 
 int PAEKS_test(char* displayMsg, unsigned char* ustr_tw, unsigned char* ustr_C1_C2, element_t pk_X, int isDisp){
	 
	element_t GT_tw, G1_C1, G1_C2;
	element_init_GT(GT_tw, pairing);
	element_init_G1(G1_C1, pairing);
	element_init_G1(G1_C2, pairing);
	 
	element_from_bytes(GT_tw, ustr_tw);
	element_from_bytes(G1_C1, ustr_C1_C2);
	element_from_bytes(G1_C2, ustr_C1_C2 + len1);
	 
	element_t GT_C2_e_g, GT_C1_e_pkX;
	element_init_GT(GT_C2_e_g, pairing);
	element_init_GT(GT_C1_e_pkX, pairing);
	
	element_pairing(GT_C2_e_g, generator, G1_C2);
	element_pairing(GT_C1_e_pkX, G1_C1, pk_X);
	
	element_t GT_tw_mul_C2_e_g;
	element_init_GT(GT_tw_mul_C2_e_g, pairing);
	
	element_mul(GT_tw_mul_C2_e_g, GT_tw, GT_C2_e_g);
	
//	***********************************************************
	/*printf("GT_tw is: \n");
	element_printf("%B", GT_tw);
	printf("\n");
	
	printf("G1_C1 is: \n");
	element_printf("%B", G1_C1);
	printf("\n");
	
	printf("G1_C2 is: \n");
	element_printf("%B", G1_C2);
	printf("\n");
	
	printf("ele_left_GT is: \n");
	element_printf("%B",GT_tw_mul_C2_e_g);
	printf("\n");
	
	printf("ele_right_GT is: \n");
	element_printf("%B",GT_C1_e_pkX);
	printf("\n\n");
	*/
	
	/*element_printf("G1_C1 is :\n%B", G1_C1);
	printf("\n");
	element_printf("G1_C2 is :\n%B", G1_C2);
	printf("\n");*/
	/*element_printf("GT_tw is :\n%B", GT_tw);
	printf("\n");*/
	
//	***********************************************************
	int cmp = element_cmp(GT_tw_mul_C2_e_g, GT_C1_e_pkX);
	
	if (isDisp){
		
		if (!cmp)
			printString(displayMsg, "1", NODISPLAY) ;
		else
			printString(displayMsg, "0", NODISPLAY) ;
			
	} //endif(idDisp)
	
	
	 return 0;
 }
 
 unsigned char* cipherToTrapdoor(unsigned char *ustr_C1_C2, element_t pk_X){
	
	element_t G1_C1, G1_C2;
	element_init_G1(G1_C1, pairing);
	element_init_G1(G1_C2, pairing);
	
	element_from_bytes(G1_C1, ustr_C1_C2);
	element_from_bytes(G1_C2, ustr_C1_C2 + len1);
	 
	element_t GT_C2_e_g, GT_C1_e_pkX;
	element_init_GT(GT_C2_e_g, pairing);
	element_init_GT(GT_C1_e_pkX, pairing);
	
	element_pairing(GT_C2_e_g, generator, G1_C2);
	element_pairing(GT_C1_e_pkX, G1_C1, pk_X);
	
	element_t GT_tw;
	element_init_GT(GT_tw, pairing);
	element_div(GT_tw, GT_C1_e_pkX, GT_C2_e_g);
	
	unsigned char *ustr_tw = malloc(len2);
	element_to_bytes(ustr_tw, GT_tw);
	
	return ustr_tw;
 }