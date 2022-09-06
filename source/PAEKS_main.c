
#include"PAEKS.h"



int PAEKS_main(char* displayMsg, PEKSkeyword *keywords, int num_of_ciphers, int num_of_senders, int keywod_num, 
		element_t * pkSenders, element_t * skSenders, int isDisp)
{
	
	printString(displayMsg, "", 0);
	
	double time_1, time_2;
	int i;
	
	//time_1 = pbc_get_time();
	
	element_t sk_x, sk_y;
	element_t pk_X, pk_Y;
	element_t sk_1, sk_2, sk_3, sk_4, sk_5;
	element_t pk_1, pk_2, pk_3, pk_4, pk_5;
	
	double time_kg_start, time_kg_stop;
	time_kg_start = pbc_get_time();
	
    PAEKS_keygen(pk_1, sk_1);
    PAEKS_keygen(pk_2, sk_2);
    PAEKS_keygen(pk_3, sk_3);
    PAEKS_keygen(pk_4, sk_4);
    PAEKS_keygen(pk_5, sk_5);
	
	time_kg_stop = pbc_get_time();
	
	printf("\nPAEKS_keygen average time: %0.3fms\n", (time_kg_stop - time_kg_start) /5* 1000);
	
	PAEKS_keygen(pk_X, sk_x);
	PAEKS_keygen(pk_Y, sk_y);
	
	unsigned char * PAEKS_Ciphertexts[num_of_ciphers];
	
	double time_encrypt;
	time_encrypt = pbc_get_time();
	
	
	PAEKS_MultiSender_Ciphertexts("", PAEKS_Ciphertexts, keywords, num_of_senders, num_of_ciphers, keywod_num, 
			skSenders, pk_X, NODISPLAY);
	
	time_encrypt = pbc_get_time() - time_encrypt;
	printf("PAEKS_Encryption Average time: %0.3f ms \n\n", (time_encrypt)/num_of_ciphers * 1000);
	
//	*********************************************
	unsigned char * trapdoors[num_of_senders];
	
	double time_trapdoor;
	time_trapdoor = pbc_get_time();
	PAEKS_MultiSender_Trapdoor("Multi-Sender TRAPDOOR: \n", trapdoors, pkSenders, num_of_senders, keywords[3], sk_x, NODISPLAY);
	time_trapdoor = pbc_get_time() - time_trapdoor;
	printf("PAEKS_Trapdoor time per keyword: %0.3f ms \n", (time_trapdoor) * 1000);
	printf("PAEKS_Trapdoor Average time per sender: %0.3f ms \n\n", (time_trapdoor)/num_of_senders * 1000);
	
	
	double time_test;
	time_test = pbc_get_time();
	for(i = 0; i < num_of_senders; i++){
		PAEKS_MultiCiphers_Test("PAEKS_MultiCiphers_Test:\n", num_of_ciphers, PAEKS_Ciphertexts, trapdoors[i], pk_X, NODISPLAY);
	}
	time_test = pbc_get_time() - time_test;
	printf("PAEKS_Test time: %d sender, %d ciphertexts: %0.3f ms \n\n",num_of_senders, num_of_ciphers, (time_test) * 1000);

//	************************************************
	
/*	
	unsigned char * test_ciphertext;
	unsigned char * test_trapdoor;
	element_t test_pk_s;
	element_t test_sk_s;
	element_t test_pk_r;
	element_t test_sk_r;
	
	PAEKS_keygen(test_pk_r, test_sk_r);
	PAEKS_keygen(test_pk_s, test_sk_s);
	
	test_ciphertext = PAEKS_encrypt("\nTest PAEKS_ENC:\n",  keywords[0], test_pk_r, test_sk_s, DISPLAY);
	
	test_trapdoor = PAEKS_trapdoor("\nTest PAEKS_TRAPDOOR:\n",  keywords[0], test_pk_s, test_sk_r, DISPLAY);
	
	PAEKS_test("\nTEST Test:\n", test_trapdoor, test_ciphertext, test_pk_r, DISPLAY);
	
	PAEKS_MultiCiphers_Test("\nTEST MULTI Test:\n", 1, &test_ciphertext, test_trapdoor, test_pk_r, DISPLAY);
*/	
	//time_2 = pbc_get_time();
	//printf("Running Time is: %0.3f ms\n", (time_2 - time_1) * 1000);
	
    return 0;
}



	
	
	