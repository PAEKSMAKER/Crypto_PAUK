/*
 * PAEKS.c
 *
 *  Created on: 2015-3-5
 *      Author: kir
 *
 * 		Implement the PEKS algorithms in PAEKS scheme.
 * 		Input a message, whose length is at most len1, the public key of the receiver, and the secret key of the sender.
 * 		Output the PAEKS ciphertext C = {C_1, C_2} with the form of unsigned char string.
 * 
 * 		PS. the input message must be initialized before inputting and padded with blank if the length of the message is 
 * 		less than len1.
 * */

#include "PAEKS.h"

//====KeyGen algorithm of PAEKS scheme====

int PAEKS_keygen(element_t public_key, element_t security_key) {
	
	keygen( public_key,  security_key) ;
	
	return 0;
}

// ====PEKS algorithm of PAEKS scheme====
unsigned char * PAEKS_encrypt(char* displayMsg, char *msg, element_t pk_X, element_t sk_y, int isDisp){
	
	unsigned char * hash_msg = malloc(SHA256_DIGEST_LENGTH);
	SHA256(msg, strlen(msg), hash_msg);
	
//	Randomly choose r from Z_p^*
	element_t ele_r;
	element_init_Zr(ele_r, pairing);
	element_random(ele_r);
	
//	Transform the hash value of the keyword into an element in G1
	unsigned char *ustr_hash_msg = malloc(SHA256_DIGEST_LENGTH);
	memcpy(ustr_hash_msg, hash_msg, SHA256_DIGEST_LENGTH);
	element_t ele_hash_msg;
	element_init_G1(ele_hash_msg, pairing);
	element_from_hash(ele_hash_msg,ustr_hash_msg, SHA256_DIGEST_LENGTH);
	
//	Initialize ciphertext C = {C_1, C_2}
	element_t ele_C_1, ele_C_2;
	element_init_G1(ele_C_1, pairing);
	element_init_G1(ele_C_2, pairing);
	
//	Initialization
	element_t ele_hash_msg_pow_sk_y;
	element_init_G1(ele_hash_msg_pow_sk_y, pairing);
	
//	Calculate the value of H(w)^{sk_s}
	element_pow_zn(ele_hash_msg_pow_sk_y, ele_hash_msg, sk_y);
	
//	Calculate the value of g^r
	element_t ele_g_pow_r;
	element_init_G1(ele_g_pow_r, pairing);
	element_pow_zn(ele_g_pow_r, generator, ele_r);
	
//	Calculate C_1 := H(w)^{sk_s} \cdot g^r
	element_mul(ele_C_1, ele_hash_msg_pow_sk_y, ele_g_pow_r); //C_1 = H(w)^sk_s \cdot g^r
	
//	Calculate C_2 := pk_R^r
	element_pow_zn(ele_C_2, pk_X, ele_r);
	
//	Generate pk_Sender
	element_t pk_Sender;
	element_init_G1(pk_Sender, pairing);
	element_pow_zn(pk_Sender, generator, sk_y);
	
//	Transform C_1, C_2 into unsigned shtring
	unsigned char * ustr_pk_c1_c2 = malloc(len1 * 3);
	element_to_bytes(ustr_pk_c1_c2, pk_Sender);
	element_to_bytes(ustr_pk_c1_c2 + len1, ele_C_1);
	element_to_bytes(ustr_pk_c1_c2 + len1 * 2, ele_C_2);
	
	if(isDisp){
		printUnsignedChar("Pk Sender: \n", ustr_pk_c1_c2, len1 );
		printUnsignedChar("hash_msg: \n", ustr_hash_msg, SHA256_DIGEST_LENGTH);
		printUnsignedChar("C1:\n", ustr_pk_c1_c2 + len1, len1);
		printUnsignedChar("C2:\n", ustr_pk_c1_c2 + len1*2, len1);
	}
	
	return ustr_pk_c1_c2;
}

//====Trapdoor algorithm of PAEKS scheme====
unsigned char * PAEKS_trapdoor(char* displayMsg, char* msg, element_t pk_Y, element_t sk_x, int isDisp){
	
	unsigned char* hash_msg = malloc(SHA256_DIGEST_LENGTH);
	SHA256(msg, strlen(msg), hash_msg);
	
//	Transform the hash value of the keyword into an element in G1
	unsigned char *ustr_hash_msg = malloc(SHA256_DIGEST_LENGTH);
	memcpy(ustr_hash_msg, hash_msg, SHA256_DIGEST_LENGTH);
	element_t ele_hash_msg;
	element_init_G1(ele_hash_msg, pairing);
	element_from_hash(ele_hash_msg,ustr_hash_msg, SHA256_DIGEST_LENGTH);
	
//	Declaration and Initialization
	element_t ele_hash_pow_sk_x;
	element_init_G1(ele_hash_pow_sk_x, pairing);
	
	element_t ele_tw;
	element_init_GT(ele_tw, pairing);
	
//	Calculate the value of H(w)^{sk_R}
	element_pow_zn(ele_hash_pow_sk_x, ele_hash_msg, sk_x);
	
//	Calculate the Bilinear pairing e(H(w)^{sk_R}, pk_Y)
	element_pairing(ele_tw, ele_hash_pow_sk_x, pk_Y);
	
	unsigned char * ustr_pk_tw = malloc(len1 + len2);
	element_to_bytes(ustr_pk_tw, pk_Y);
	element_to_bytes(ustr_pk_tw + len1, ele_tw);
	if(isDisp){
	printUnsignedChar("Pk_sender: \n", ustr_pk_tw, len1);
	printUnsignedChar("Tw:\n", ustr_pk_tw+len1, len2);
	}
	return ustr_pk_tw;
}

//====Test algrithm of PAEKS scheme====
int PAEKS_test(char* displayMsg, unsigned char* ustr_tw, unsigned char* ustr_C1_C2, element_t pk_X, int isDisp){
	 
	element_t GT_tw, G1_C1, G1_C2;
	element_init_GT(GT_tw, pairing);
	element_init_G1(G1_C1, pairing);
	element_init_G1(G1_C2, pairing);
	 
	//ustr_tw = pkSender||Tw
	element_from_bytes(GT_tw, ustr_tw + len1);
	//ustr_C1_C2 = pkSender||C1||C2
	element_from_bytes(G1_C1, ustr_C1_C2 + len1);
	element_from_bytes(G1_C2, ustr_C1_C2 + len1 * 2);
	
/*
*	printUnsignedChar("ustr_tw in PAEKS_test:\n", ustr_tw+ len1, len2);
*	printUnsignedChar("ustr_C1 in PAEKS_test\n", ustr_C1_C2+len1, len1);
*	printUnsignedChar("ustr_C2 in PAEKS_test\n", ustr_C1_C2+len1*2, len1);
*	print_element("G1_C1 in PAEKS_test:\n", G1_C1);
*	print_element("G1_C2 in PAEKS_test:\n", G1_C2);
*/
	element_t GT_C2_e_g, GT_C1_e_pkX;
	element_init_GT(GT_C2_e_g, pairing);
	element_init_GT(GT_C1_e_pkX, pairing);
	
	element_pairing(GT_C2_e_g, generator, G1_C2);
	element_pairing(GT_C1_e_pkX, G1_C1, pk_X);
	
	element_t GT_tw_mul_C2_e_g;
	element_init_GT(GT_tw_mul_C2_e_g, pairing);
	
	element_mul(GT_tw_mul_C2_e_g, GT_tw, GT_C2_e_g);
	
	int cmp = element_cmp(GT_tw_mul_C2_e_g, GT_C1_e_pkX);
	
//	print_element("GT_tw_mul_C2_e_g:\n", GT_tw_mul_C2_e_g);
//	print_element("GT_C1_e_pkX:\n", GT_C1_e_pkX);
	
	if (isDisp){
		
		if (!cmp)
			printString(displayMsg, "1", NODISPLAY) ;
		else
			printString(displayMsg, "0", NODISPLAY) ;
			
	} //endif(isDisp)
	
	 return (!cmp);
 }
 
 