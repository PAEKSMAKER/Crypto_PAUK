

#include "common.h"

#ifndef PRAEK_H
#define PRAEK_H

int PRAEK_keygen_Receiver(element_t G1_pkR1, element_t G1_pkR2 , element_t G1_pkR3, 
		element_t Zr_skR1, element_t Zr_skR2, element_t Zr_skR3, element_t Zr_skR4);
int PRAEK_keygen_Sender(element_t G1_pkS1, element_t Zr_skS1);
void PRAEK_Hash(unsigned char * hash_result, element_t ele, char *msg);

unsigned char* PRAEK_encrypt(char* displayMsg, char *msg, element_t pk_R1, element_t pk_R2, element_t pk_R3, 
			element_t sk_Sender, int isDisp);
 unsigned char * PRAEK_Re_Enc(char* displayMsg, unsigned char* ustr_C1_C2_C3_C4_C5, 
			element_t Zr_rk, int isDisp);
			
unsigned char* PRAEK_trapdoor(char* displayMsg, char* msg, element_t pk_Sender, element_t sk_R1, 
			element_t sk_R2, element_t sk_R3, int isDisp);
unsigned char * PRAEK_Re_trapdoor(char * displayMsg, unsigned char * ustr_Tw1_Tw2, char* msg, 
			element_t Zr_skR4, int isDisp);

int PRAEK_test(char* displayMsg, unsigned char* ustr_Tw1_Tw2, unsigned char* ustr_C1_C2, int isDisp);
int PRAEK_Re_test(char* displayMsg, unsigned char* ustr_Tw1_Tw2, unsigned char* ustr_C1_C2_C3_C4_C5, int isDisp);


int PRAEK_Equality_Test(char * dispMsg, unsigned char * ustr_Re_C1, unsigned char * ustr_Re_C2, int isDisp);





typedef struct Ciphertext_Link{
	struct Ciphertext_Link * P_Pre;
	
	unsigned char * Ciphertext;
	
	struct Ciphertext_Link * P_Next;
} PRAEK_CLink;

typedef struct PRAEK_Index{
	struct PRAEK_Index * P_Pre;
	
	int Index_Num;
	unsigned char * Label_Ciphertext;
	int Num_of_Record;
	struct Ciphertext_Link * P_Clink;
	
	struct PRAEK_Index * P_Next;
} PRAEK_Index;



PRAEK_CLink * init_CLink(PRAEK_Index * p_index, unsigned char * PRAEK_C1_to_C5);
PRAEK_CLink * insert_Cipher_CLink(PRAEK_Index * p, unsigned char * PRAEK_C1_to_C5, int add);
PRAEK_Index * init_Index();
PRAEK_Index * insert_Index(PRAEK_Index * p, int add);
void displayLink(PRAEK_CLink *p);
void PRAEK_Invert_Index_build(char * dispMsg,  PRAEK_Index * p_Index, unsigned char * ciphertext, int isDisp);

 int PRAEK_MultiCiphers_Test(char * dispMsg, int ciphertexts_num, unsigned char * PRAEK_Ciphertexts[], 
			unsigned char * trapdoor, int isDisp);
int PRAEK_MultiSender_Trapdoor(char * displayMsg, unsigned char * trapdoors[], element_t pkSenders[], 
			int num_of_senders, char * keyword, element_t Zr_sk_R1, element_t Zr_sk_R2, element_t Zr_sk_R3, int isDisp);
int PRAEK_MultiSender_Ciphertexts(char * displayMsg, unsigned char * PRAEK_Ciphertexts[], PEKSkeyword *keywords, int num_of_senders, 
			int num_of_ciphers, int keywod_num, element_t skSenders[], element_t G1_pk_R1, element_t G1_pk_R2, element_t G1_pk_R3, int isDisp);
int PRAEK_Fast_Search(char * dispMsg, PRAEK_Index * p, unsigned char * RTrapdoor, int isDisp);

#endif /* PRAEK_H*/
