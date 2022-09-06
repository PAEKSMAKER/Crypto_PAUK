
/*	trapdoor.c
 * 
 * 		Created on: 2017-2-22	
 * 			Author: kir
 * 
 * */

#include "PAEKS_main.h"

unsigned char* PAEKS_trapdoor(char* displayMsg, char* msg, element_t pk_Y, element_t sk_x, int isDisp){
	
	
	
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
	
	unsigned char* ustr_tw = malloc(len2);
	element_to_bytes(ustr_tw, ele_tw);
	
//	*********************************************
	/*element_printf("ele_tw is :\n%B", ele_tw);
	printf("\n");*/
//	element_printf("ele_hash_msg is :\n%B", ele_hash_msg);
	printf("\n");
//	printf("Ustr_hash_msg is: \n");
//	int i;
//	for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//		printf("%02X", ustr_hash_msg[i]);
//	}

	
	
	if(isDisp){
	printUnsignedChar(displayMsg, ustr_tw, len2);
	printUnsignedChar("Hash msg is: \n", ustr_hash_msg, SHA256_DIGEST_LENGTH);
	}
	
	return ustr_tw;
}



