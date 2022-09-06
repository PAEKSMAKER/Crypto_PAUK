


#include "PAEKS.h"

//====cipherToTrapdoor====
 
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
 
 
 
 //	====Multi Ciphertexts Test====
 
 int PAEKS_MultiCiphers_Test(char * dispMsg, int ciphertexts_num, unsigned char * PAEKS_Ciphertexts[], 
			unsigned char * trapdoor, element_t ele_pk_Receiver, int isDisp){
				
	element_t ele_pk_Sender_of_Tw;
	element_init_G1(ele_pk_Sender_of_Tw, pairing);
	element_from_bytes(ele_pk_Sender_of_Tw, trapdoor);
	
//	print_element("Trapdoor in Multi Ciphertext: \n", ele_pk_Sender_of_Tw);
	element_t ele_pk_Sender_of_Cipher;
	element_init_G1(ele_pk_Sender_of_Cipher, pairing);
	
	
	int i; 
	for(i = 0; i < ciphertexts_num; i++){
		element_from_bytes(ele_pk_Sender_of_Cipher, PAEKS_Ciphertexts[i]);
//		print_element("", ele_pk_Sender_of_Cipher);
		if (!element_cmp(ele_pk_Sender_of_Tw, ele_pk_Sender_of_Cipher)){
			
			if(PAEKS_test("", trapdoor , PAEKS_Ciphertexts[i] , ele_pk_Receiver, NODISPLAY)){
				if(isDisp){
					printf("Matched Ciphertext:%3d\n", i);			
				}
			}
		}
	}
	printf("");
	return 0;
}


//	====PAEKS MultSender Trapdoor====

int PAEKS_MultiSender_Trapdoor(char * displayMsg, unsigned char * trapdoors[], element_t pkSenders[], 
			int num_of_senders, char * keyword, element_t Zr_sk_receiver, int isDisp){
	
	int i;
	printString(displayMsg, "", 0);
	for(i = 0; i < num_of_senders; i++){
		if(isDisp)
			printf("Trapdoor %d: \n", i);
		trapdoors[i] = PAEKS_trapdoor("Trapdoor: \n", keyword, pkSenders[i], Zr_sk_receiver, isDisp);
		if(isDisp)
			printString("Keyword:\n", keyword, NODISPLAY);
	}
	return 0;
}


//	====PAEKS Multi-Sender Ciphertexts====

int PAEKS_MultiSender_Ciphertexts(char * displayMsg, unsigned char * PAEKS_Ciphertexts[], PEKSkeyword *keywords, 
		int num_of_senders, int num_of_ciphers, int keywod_num, element_t skSenders[], element_t pk_receiver, int isDisp){
	
	int i;
	int rand_sender = 0;
	int rand_kw = 0;
	
	for(i = 0; i < num_of_ciphers; i++){
		rand_sender = random_sender(0, num_of_senders);
		rand_kw = random_num(keywod_num, 0);
		if (isDisp)
			printf("PAEKS_MultiSender_Ciphertext %d: ", i);
		PAEKS_Ciphertexts[i] = PAEKS_encrypt("\nPAEKS_Ciphertext C1||C2: \n", keywords[rand_kw], pk_receiver, 
		skSenders[rand_sender], isDisp);
		if(isDisp)
			printString("Keywords:", keywords[rand_kw], NODISPLAY);
	}
	return 0;
}

