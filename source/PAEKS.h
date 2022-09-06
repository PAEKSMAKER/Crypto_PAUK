

/*
 * PAEKS.h
 *
 *  Created on: 2021-9-28
 *      Author: kir
 */

#include "common.h"

#ifndef PAEKS_H_
#define PAEKS_H_



int PAEKS_keygen(element_t public_key, element_t security_key);
unsigned char * PAEKS_encrypt(char* displayMsg, char *msg, element_t pk_X, element_t sk_y, int isDisp);
unsigned char * PAEKS_trapdoor(char* displayMsg, char* msg, element_t pk_Y, element_t sk_x, int isDisp);
int PAEKS_test(char* displayMsg, unsigned char* ustr_tw, unsigned char* ustr_C1_C2, element_t pk_X, int isDisp);
unsigned char* cipherToTrapdoor(unsigned char *ustr_C_1_C_2, element_t pk_X);
int PAEKS_MultiCiphers_Test(char * dispMsg, int ciphertexts_num, unsigned char * PAEKS_Ciphertexts[], 
			unsigned char * trapdoor, element_t ele_pk_Receiver, int isDisp);
int PAEKS_MultiSender_Trapdoor(char * displayMsg, unsigned char * trapdoors[], element_t  pkSenders[], 
			int num_of_senders, char * keyword, element_t Zr_sk_receiver, int isDisp);
int PAEKS_MultiSender_Ciphertexts(char * displayMsg, unsigned char * PAEKS_Ciphertexts[], PEKSkeyword *keywords, int num_of_senders, 
			int num_of_ciphers, int keywod_num, element_t skSenders[], element_t pk_receiver, int isDisp);

	
#endif /* PAEKS_H_ */