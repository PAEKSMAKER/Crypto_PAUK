/*
 * PAEKS_keyGen.c
 *
 *  Created on: 2021-09-28
 * 
 *      Author: kir
 *
 * 		Implement the KeyGen algorithm in PAEKS scheme.
 * 		Input:	 	public parameter (pp).	
 * 		Output:	 public/secret key pairing (pkR/skR) and (pkS, skS).
 * 
 * 		Same as the keyGen algorithm in Setup.c
 * 
 * */
 
 #include "PRAEK_main.h"

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


int PRAEK_Re_keygen(element_t Zr_rk, element_t G1_pkSender, element_t Zr_skR1, element_t Zr_skR2, 
			element_t Zr_skR3, element_t Zr_skR4){
	
	//sharing key
	element_t sharingK;
	element_init_G1(sharingK, pairing);
	element_pow_zn(sharingK, G1_pkSender, Zr_skR1);
	print_element("Re-keygen: sharingK \n", sharingK);
	
	//H1(shrK)
	element_t Zr_denominator;
	PRAEK_Hash_1_FromG1_ToZr(Zr_denominator, sharingK, pairing);
	element_mul_zn(Zr_denominator, Zr_skR2, Zr_denominator);
	element_add(Zr_denominator, Zr_denominator, Zr_skR3);
	print_element("Re-keygen: Zr_denominator \n", Zr_denominator);
	
	//rk
	element_init_Zr(Zr_rk, pairing);
	element_div(Zr_rk, Zr_skR4, Zr_denominator);
	print_element("Zr_skR4:\n", Zr_skR4);
	print_element("Re-encryption key: \n", Zr_rk);
	
	return 0;	
}




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
	 
