/*
 * PAEKS_Appendix.c
 *
 *  Created on: 2021-09-28
 * 
 *      Author: kir
 *
 * 		Other algorithms of PRAEKS scheme.
 * 
 * */

#include "PRAEK.h"

 void PRAEK_Hash_ElementChar_SHA256(unsigned char * hash_result, element_t ele, char *msg){
	 
	 int len_ele = element_length_in_bytes(ele);
	 int len_msg = strlen(msg);
	 unsigned char * ustr_ele11msg = malloc(len_ele+len_msg);
	 memcpy(ustr_ele11msg, msg, len_msg);
	 element_to_bytes(ustr_ele11msg + len_msg, ele);
	 
	 SHA256(ustr_ele11msg, len_ele+len_msg, hash_result);
 }
 
 void PRAEK_Hash_1_FromG1_ToZr(element_t Zr_output, element_t G1_input, pairing_t pairing){
	//H(shrK)
	unsigned char * ustr_hash_shrK = malloc(SHA256_DIGEST_LENGTH);
	PRAEK_Hash_ElementChar_SHA256(ustr_hash_shrK, G1_input, "");

	element_init_Zr(Zr_output, pairing);
	element_from_hash(Zr_output, ustr_hash_shrK, SHA256_DIGEST_LENGTH);
}

void PRAEK_Hash_FromG1timeschar_ToZr(element_t Zr_output, element_t G1_input, char* Str_input, pairing_t pairing){
	// H(shrK, w)
	unsigned char * ustr_hash_msg = malloc(SHA256_DIGEST_LENGTH);
	PRAEK_Hash_ElementChar_SHA256(ustr_hash_msg, G1_input, Str_input);
	
	element_init_Zr(Zr_output, pairing);
	element_from_hash(Zr_output, ustr_hash_msg, SHA256_DIGEST_LENGTH);
}
 
void PRAEK_Hash_2_FromChar_ToElement(element_t ele_hash_result, char * str_input, int groupType){
	
	if (groupType == 1){
		element_init_G1(ele_hash_result, pairing);
	}
	else if (groupType == 2){
		element_init_G2(ele_hash_result, pairing);
	}
	else if(groupType == 3){
		element_init_GT(ele_hash_result, pairing);
	}
	else {
		printf("Wrong group type!!\n");
	}
	
	int len_input_msg = strlen(str_input);
	int len_ele = element_length_in_bytes(ele_hash_result);
	
	unsigned char * ustr_hash_result = malloc(SHA256_DIGEST_LENGTH);
	SHA256(str_input, len_input_msg, ustr_hash_result);
	
	element_from_hash(ele_hash_result, ustr_hash_result, SHA256_DIGEST_LENGTH);
	
}

//====Ciphertexts Link====

PRAEK_CLink * init_CLink(PRAEK_Index * p_index, unsigned char * PRAEK_C1_to_C5){
	PRAEK_CLink * p = (PRAEK_CLink*) malloc(sizeof(PRAEK_CLink));
	
	
	p->P_Pre = NULL;
	p->P_Next = NULL;
	
	p->Ciphertext = (unsigned char *)malloc(sizeof(len1 * 5));
	memcpy(p->Ciphertext, PRAEK_C1_to_C5, len1*5);
	
	p_index->P_Clink = p;
	p_index->Label_Ciphertext = p->Ciphertext;
	
	return p;
}

PRAEK_CLink * insert_Cipher_CLink(PRAEK_Index * p, unsigned char * PRAEK_C1_to_C5, int add){
	PRAEK_CLink * temp = p->P_Clink;
	for(int i=1; i < add; i++){
		if(temp == NULL){
			printf("Invalid Inserted Place\n");
			return p->P_Clink;
		}
		temp = temp->P_Next;
	}
//	Create inserted node
	PRAEK_CLink * c = (PRAEK_CLink *)malloc(sizeof(PRAEK_CLink));
	unsigned char * c_ciphertext = malloc(len1 *5);
	memcpy(c_ciphertext, PRAEK_C1_to_C5, len1 * 5);
	c->Ciphertext = c_ciphertext;
	
//	Insert node into the link
	if(p->Num_of_Record == 0){
		p->P_Clink = c; 
		p->Label_Ciphertext = p->P_Clink->Ciphertext;
	}
	else{
		c->P_Next = temp->P_Next;
		temp->P_Next = c;
		c->P_Pre=temp;
	}
	p->Num_of_Record++;
	
	return p->P_Clink;
}

//====Index Link====

PRAEK_Index * init_Index(){
	PRAEK_Index * p = (PRAEK_Index*)malloc(sizeof(PRAEK_Index));
	
	p->Index_Num = 0;
	p->Label_Ciphertext = NULL;
	p->Num_of_Record = 0;
	p->P_Clink = NULL;
	p->P_Pre = NULL;
	p->P_Next = NULL;
	
	return p;
}

PRAEK_Index * insert_Index(PRAEK_Index * p, int add){
	PRAEK_Index * temp = p;
	
	for(int i=1; i<add; i++){
		if(temp == NULL){
			printf("Invalid Inserted Place\n");
			return p;
		}
		temp = temp->P_Next;
	}
//	Create Inserted Point
	PRAEK_Index * c = (PRAEK_Index*)malloc(sizeof(PRAEK_Index));
	c->Num_of_Record = 0;
	c->P_Clink = NULL;
	c->Label_Ciphertext = NULL;
	c->Index_Num = (temp->Index_Num) + 1;
	
//	Insert node into the link
	c->P_Next = temp->P_Next;
	temp->P_Next = c;
	c->P_Pre = temp;
	
	return p;
}

void displayLink(PRAEK_CLink *p){
	
	PRAEK_CLink * temp = p;
	
	while(temp->P_Next){
		temp = temp->P_Next;
		printUnsignedChar("", temp->Ciphertext, 10);
	}
	printf("\n");
}
	
void PRAEK_Invert_Index_build(char * dispMsg,  PRAEK_Index * p_Index, unsigned char * ciphertext, int isDisp){
	
	PRAEK_Index * temp = p_Index;
	int existMatchedLabel = 0;
	unsigned char * ustr_labelCiphertext = malloc(len1 * 5);
	
	while(!existMatchedLabel && temp->P_Next ){
		temp = temp->P_Next;
		memcpy(ustr_labelCiphertext, temp->Label_Ciphertext, len1 * 5);
		
		existMatchedLabel = PRAEK_Equality_Test("", ciphertext, ustr_labelCiphertext, NODISPLAY);
		if (existMatchedLabel){
			insert_Cipher_CLink(temp, ciphertext, 1);
			if(NODISPLAY){
				printString(dispMsg, "", 0);
				printf("Index No.%d:\n", temp->Index_Num);
				printUnsignedChar("Cipher (Partial): ", ciphertext, 20);
			}
			return;
		}
	}
	if(!existMatchedLabel){
		insert_Index(temp, 1);
		temp = temp->P_Next;
		insert_Cipher_CLink(temp, ciphertext, 1);
		if(NODISPLAY){
				printString(dispMsg, "", 0);
				printf("Index No.%d:\n", temp->Index_Num);
				printUnsignedChar("Cipher (Partial): ", ciphertext, 20);
		}
	}
	return;
}	

int PRAEK_Equality_Test(char * dispMsg, unsigned char * ustr_Re_C1, unsigned char * ustr_Re_C2, int isDisp){
	
	int testResult = 0;
	if (ustr_Re_C1 == NULL || ustr_Re_C2 == NULL){
		testResult = 0;
		return testResult;
	}
	
	unsigned char * C4_C5 = malloc(len1 * 2);
	unsigned char * C5_C4_prime = malloc(len1 * 2);
	
	memcpy(C4_C5, ustr_Re_C1 + len1 * 3, len1 * 2);
	memcpy(C5_C4_prime, ustr_Re_C2 + len1 * 4, len1);
	memcpy(C5_C4_prime+len1, ustr_Re_C2 + len1 * 3, len1);
	
	testResult = PRAEK_test(dispMsg, C4_C5, C5_C4_prime, isDisp);
	
	return testResult;
}
	
int PRAEK_Fast_Search(char * dispMsg, PRAEK_Index * p, unsigned char * RTrapdoor, int isDisp){
	
	int i = 0;
	int existMatchedCipher = 0;
	PRAEK_Index * temp = p;
	PRAEK_CLink * temp_CLink;
	
	while(temp->P_Next){
		temp = temp->P_Next;
		existMatchedCipher = PRAEK_Re_test(dispMsg, RTrapdoor, temp->Label_Ciphertext, isDisp);
		if(existMatchedCipher){
			printf("Matched Cipher Index: %d\n", temp->Index_Num);
			printf("Matched Cipher Numbers: %d\n", temp->Num_of_Record);
			temp_CLink = temp->P_Clink;
			i = 0;
			while(i++ < temp->Num_of_Record){
				printf("No.%2d: ", i);
				printUnsignedChar("", temp_CLink->Ciphertext, 20);
				temp_CLink = temp_CLink->P_Next;
			}//end while
		}//end if
	}//end while
	
	return i;
}
	
	
	 
 //	====Multi Ciphertexts Test====
	
 
 int PRAEK_MultiCiphers_Test(char * dispMsg, int ciphertexts_num, unsigned char * PRAEK_Ciphertexts[], 
			unsigned char * trapdoor, int isDisp){
				
	element_t ele_pk_Sender_of_Tw;
	element_init_G1(ele_pk_Sender_of_Tw, pairing);
	element_from_bytes(ele_pk_Sender_of_Tw, trapdoor + len1 * 2);
	
//	print_element("Trapdoor in Multi Ciphertext: \n", ele_pk_Sender_of_Tw);
	element_t ele_pk_Sender_of_Cipher;
	element_init_G1(ele_pk_Sender_of_Cipher, pairing);
	
	
	int i; 
	int matchedNum = 1;
	for(i = 0; i < ciphertexts_num; i++){
		element_from_bytes(ele_pk_Sender_of_Cipher, PRAEK_Ciphertexts[i] + len1 * 4);
//		print_element("", ele_pk_Sender_of_Cipher);
		if (!element_cmp(ele_pk_Sender_of_Tw, ele_pk_Sender_of_Cipher)){
			
			if(PRAEK_test("", trapdoor, PRAEK_Ciphertexts[i], NODISPLAY)){
				printf("No.%2d: Matched Ciphertext %3d\n", matchedNum++, i);
			}
		}
	}
	printf("");
	return 0;
}


//	====PRAEK MultSender Trapdoor====

int PRAEK_MultiSender_Trapdoor(char * displayMsg, unsigned char * trapdoors[], element_t pkSenders[], 
			int num_of_senders, char * keyword, element_t Zr_sk_R1, element_t Zr_sk_R2, element_t Zr_sk_R3, int isDisp){
	
	int i;
	printString(displayMsg, "", 0);
	for(i = 0; i < num_of_senders; i++){
		if(isDisp)
			printf("Trapdoor %d: \n", i);
		trapdoors[i] = PRAEK_trapdoor("Trapdoor: \n", keyword, pkSenders[i], Zr_sk_R1, Zr_sk_R2, Zr_sk_R3, isDisp);
		if(isDisp)
			printString("Keyword:\n", keyword, NODISPLAY);
	}
	return 0;
}


//	====PAEKS Multi-Sender Ciphertexts====




int PRAEK_MultiSender_Ciphertexts(char * displayMsg, unsigned char * PRAEK_Ciphertexts[], PEKSkeyword *keywords, int num_of_senders, 
			int num_of_ciphers, int keyword_num, element_t skSenders[], element_t G1_pk_R1, element_t G1_pk_R2, element_t G1_pk_R3, int isDisp){
	
	int i;
	int rand_sender = 0;
	int rand_kw = 0;
	
	
	
	
	for(i = 0; i < num_of_ciphers; i++){
		rand_sender = random_sender(0, num_of_senders);
		rand_kw = random_num(keyword_num, 0);
		if (isDisp)
			printf("PAEKS_MultiSender_Ciphertext %d: ", i);
		PRAEK_Ciphertexts[i] = PRAEK_encrypt("\nPRAEK_Ciphertext: \n", keywords[rand_kw], 
				G1_pk_R1, G1_pk_R2, G1_pk_R3, skSenders[rand_sender], isDisp);
				
		if(isDisp)
			printString("Keywords:", keywords[rand_kw], NODISPLAY);
	}
	return 0;
}


