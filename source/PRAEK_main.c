




#include"PRAEK.h"

int PRAEK_main(char* displayMsg, PEKSkeyword *keywords, int num_of_ciphers, int num_of_senders,  int keywod_num, 
		element_t * pkSenders, element_t * skSenders, int isDisp){
	
	printString(displayMsg, "", 0);		
			
	int i = 0;
	int j = 0;
	element_t pk_1, pk_2, pk_3, pk_4, pk_5;
	element_t pk_R1, pk_R2, pk_R3;
	
	element_t sk_1, sk_2, sk_3, sk_4, sk_5;
	element_t sk_R1, sk_R2, sk_R3, sk_R4;

	double time_kg_start, time_kg_stop;
	
	time_kg_start = pbc_get_time();
	PRAEK_keygen_Receiver(pk_R1, pk_R2, pk_R3, sk_R1, sk_R2, sk_R3, sk_R4);
	PRAEK_keygen_Receiver(pk_R1, pk_R2, pk_R3, sk_R1, sk_R2, sk_R3, sk_R4);
	PRAEK_keygen_Receiver(pk_R1, pk_R2, pk_R3, sk_R1, sk_R2, sk_R3, sk_R4);
	PRAEK_keygen_Receiver(pk_R1, pk_R2, pk_R3, sk_R1, sk_R2, sk_R3, sk_R4);
	PRAEK_keygen_Receiver(pk_R1, pk_R2, pk_R3, sk_R1, sk_R2, sk_R3, sk_R4);
	time_kg_stop = pbc_get_time();
	printf("\nPRAEK_keygen_Receiver average time: %0.3f ms \n", (time_kg_stop - time_kg_start) /5 * 1000);
	
	//print_element("sk_R3 in PRAEK_main:", sk_R3);
	time_kg_start = pbc_get_time();
	
	PRAEK_keygen_Sender(pk_1, sk_1);
	PRAEK_keygen_Sender(pk_2, sk_2);
	PRAEK_keygen_Sender(pk_3, sk_3);
	PRAEK_keygen_Sender(pk_4, sk_4);
	PRAEK_keygen_Sender(pk_5, sk_5);
	
	time_kg_stop = pbc_get_time();
	printf("\nPRAEK_keygen_Sender average time: %0.3f ms \n", (time_kg_stop - time_kg_start) /5* 1000);
	
	unsigned char* Ciphertext_1, *Ciphertext_2;
	Ciphertext_1 = PRAEK_encrypt("\nPRAEK Ciphertext 1 C1||C2: \n", keywords[1], pk_R1, pk_R2, pk_R3, skSenders[1], NODISPLAY);
	Ciphertext_2 = PRAEK_encrypt("\nPRAEK Ciphertext 2 C1||C2: \n", keywords[2], pk_R1, pk_R2, pk_R3, skSenders[2], NODISPLAY);
	
	unsigned char* trapdoor_1, *trapdoor_2;
	trapdoor_1 = PRAEK_trapdoor("\nPRAEK Trapdoor 1: \n", keywords[1], pkSenders[1], sk_R1, sk_R2, sk_R3, NODISPLAY);
	trapdoor_2 = PRAEK_trapdoor("\nPRAEK Trapdoor 2: \n", keywords[2], pkSenders[2], sk_R1, sk_R2, sk_R3, NODISPLAY);
	
	int test_1_1, test_1_2, test_2_1, test_2_2;
	
	double time_start_test, time_stop_test;
	time_start_test = pbc_get_time();
	
	test_1_1 = PRAEK_test("PRAEK_Test Tw1, C1: ", trapdoor_1, Ciphertext_1, NODISPLAY);
	test_1_2 = PRAEK_test("PRAEK_Test Tw1, C2: ", trapdoor_1, Ciphertext_2, NODISPLAY);
	test_2_1 = PRAEK_test("PRAEK_Test Tw2, C1: ", trapdoor_2, Ciphertext_1, NODISPLAY);
	test_2_2 = PRAEK_test("PRAEK_Test Tw2, C2: ", trapdoor_2, Ciphertext_2, NODISPLAY);
	
	time_stop_test = pbc_get_time();
	printf("PRAEK_Test time: %0.3f ms \n\n", (time_stop_test - time_start_test) * 1000);
	
	element_t Zr_rks[num_of_senders];
	
	double time_rkGen;
	time_rkGen = pbc_get_time();
	PRAEK_Re_keygen("PRAEK_Re_kegen \/\/", Zr_rks[1], pkSenders[1], sk_R1, sk_R2, sk_R3, sk_R4, NODISPLAY);
	PRAEK_Re_keygen("", Zr_rks[2], pkSenders[2], sk_R1, sk_R2, sk_R3, sk_R4, NODISPLAY);
	time_rkGen = pbc_get_time() - time_rkGen;
	printf("PRAEK_ReKGen time: %0.3f ms \n\n", time_rkGen / 2 * 1000);
	
	Ciphertext_1 = PRAEK_Re_Enc("\nPRAEK ReEnc Ciphertext 1 C1~C5: \n", Ciphertext_1, Zr_rks[1], NODISPLAY);
	Ciphertext_2 = PRAEK_Re_Enc("\nPRAEK ReEnc Ciphertext 2 C1~C5: \n", Ciphertext_2, Zr_rks[2], NODISPLAY);
	
	trapdoor_1 = PRAEK_Re_trapdoor("\nTrapdoor of kw 1: \n", trapdoor_1, keywords[1], sk_R4, NODISPLAY);
	trapdoor_2 = PRAEK_Re_trapdoor("\nTrapdoor of kw 2: \n", trapdoor_2, keywords[2], sk_R4, NODISPLAY);
	
	double time_start_ReTest, time_stop_ReTest;
	
	time_start_ReTest = pbc_get_time();
	test_1_1 = PRAEK_Re_test("PRAEK_Re_Test Tw1, C1:", trapdoor_1, Ciphertext_1, NODISPLAY);
	test_1_2 = PRAEK_Re_test("PRAEK_Re_Test Tw1, C2:", trapdoor_1, Ciphertext_2, NODISPLAY);
	test_2_1 = PRAEK_Re_test("PRAEK_Re_Test Tw2, C1:", trapdoor_2, Ciphertext_1, NODISPLAY);
	test_2_2 = PRAEK_Re_test("PRAEK_Re_Test Tw2, C2:", trapdoor_2, Ciphertext_2, NODISPLAY);
	time_stop_ReTest = pbc_get_time();
	
	printf("PRAEK_Re_Test time: %0.3f ms \n\n", (time_stop_ReTest - time_start_ReTest) * 1000);
	
	SenderEnroll("Enroll Senders: \n", 2, pkSenders, skSenders, NODISPLAY);
	
	PRAEK_Index * InvertIndex = init_Index();
	
	PRAEK_Invert_Index_build("Insert C1 into Index", InvertIndex, Ciphertext_1, NODISPLAY);
	PRAEK_Invert_Index_build("Insert C2 into Index", InvertIndex, Ciphertext_2, NODISPLAY);
	
	
//	==========Multi Sender Algorithms==========
	
//	====Multi Sender Ciphertexts====
	
	unsigned char * PRAEK_Ciphertexts[num_of_ciphers];
	
	double time_encrypt;
	time_encrypt = pbc_get_time();
	PRAEK_MultiSender_Ciphertexts("", PRAEK_Ciphertexts, keywords, num_of_senders, num_of_ciphers, keywod_num,
			skSenders, pk_R1, pk_R2, pk_R3, isDisp);
	time_encrypt = pbc_get_time() - time_encrypt;
	printf("PRAEK_Encryption Average time: %0.3f ms \n\n", (time_encrypt)/num_of_ciphers * 1000);
	
	
	
//	====Multi Sender Trapdoor====

	unsigned char * trapdoors[num_of_senders];
	
	double time_trapdoor;
	time_trapdoor = pbc_get_time();
	
	PRAEK_MultiSender_Trapdoor("Multi-Sender TRAPDOOR: \n", trapdoors, pkSenders, num_of_senders, 
			keywords[3], sk_R1, sk_R2, sk_R3, NODISPLAY);
	
	time_trapdoor = pbc_get_time() - time_trapdoor;
	printf("PRAEK_MultiSender_Trapdoor generation time per keyword: %0.3f ms \n\n", (time_trapdoor) * 1000);
	printf("PRAEK_MultiSender_Trapdoor generation time per trapdoor: %0.3f ms \n\n", (time_trapdoor)/num_of_senders * 1000);
	
	
	
//====Multi Sender Test====
	
	double time_test;
	time_test = pbc_get_time();
	for(i = 0; i < num_of_senders; i++){
		if(isDisp){
			printf("trapdoor for sender %d:\n", i);	
		}

		PRAEK_MultiCiphers_Test("PRAEK_MultiCiphers_Test:\n", num_of_ciphers, PRAEK_Ciphertexts, trapdoors[i], DISPLAY);
		
	}
	time_test = pbc_get_time() - time_test;
	printf("PRAEK_Test time: %d sender, %d ciphertexts: %0.3f ms \n\n",num_of_senders, num_of_ciphers, (time_test) * 1000);
	
	
	
//	====PRAEK Re-keygen====
	
	double time_rekeygen;
	time_rekeygen = pbc_get_time();
	
	for(i = 0; i < num_of_senders; i++){
		if(isDisp){
			printf("ReKGen%2d:", i);
		}
		PRAEK_Re_keygen("", Zr_rks[i], pkSenders[i], sk_R1, sk_R2, sk_R3, sk_R4, NODISPLAY);
		
	}
	
	time_rekeygen = pbc_get_time() - time_rekeygen;
	
//	====PRAEK Re-encryption====
	
	
	double time_reencryption;
	int senderID = -1;
	element_t G1_pk_in_cipher;
	element_init_G1(G1_pk_in_cipher, pairing);
	
	time_reencryption = pbc_get_time();
	for(i = 0; i < num_of_ciphers; i++){
		
		for(j = 0; j < num_of_senders; j++){
			element_from_bytes(G1_pk_in_cipher, PRAEK_Ciphertexts[i] + len1 * 4);
			if(!element_cmp(G1_pk_in_cipher, pkSenders[j])){
				senderID = j;
				if(isDisp){
					printf("SenderID: %d\n", j);
				}
				break;
			}//end If
		}// end for
		
//		printUnsignedChar("PRAEK cipher before Reencryption: \n", PRAEK_Ciphertexts[i] + len1 * 4 - 20, 40);
		
		PRAEK_Re_Enc("\n", PRAEK_Ciphertexts[i], Zr_rks[senderID], NODISPLAY);
//		printUnsignedChar("PRAEK cipher after Reencryption: \n", PRAEK_Ciphertexts[i]+ len1 * 4 - 20, 40);
		
	}
	time_reencryption = pbc_get_time() - time_reencryption;
	printf("PAEKS_Re_encryption time: %0.3f ms \n\n", (time_reencryption) * 1000);
	
	
//	==========Fast Seaching Algorithms==========
	
//	====Building Fast Searching Index====
	
	PRAEK_Index * FastSearchingIndex = init_Index();
	
	double time_fastsearchingIndex;
	time_fastsearchingIndex = pbc_get_time();
	for(i = 0; i < num_of_ciphers; i++){
		
		PRAEK_Invert_Index_build("", FastSearchingIndex, PRAEK_Ciphertexts[i], DISPLAY);
	
	}
	
	time_fastsearchingIndex = pbc_get_time() - time_fastsearchingIndex;
	printf("\nBuliding Fast Searching Index time: %0.3f ms \n\n", (time_fastsearchingIndex) * 1000);
	printf("\nBuliding Fast Searching Index time per cipher: %0.3f ms \n\n", (time_fastsearchingIndex)/num_of_ciphers * 1000);
	



//	====Fast Searching====

	unsigned char * RTrapdoor = malloc(len1 * 2);
	double time_Re_trapdoor;
	time_Re_trapdoor = pbc_get_time();
	RTrapdoor = PRAEK_Re_trapdoor("\nTrapdoor of kw 2: \n", RTrapdoor, keywords[3], sk_R4, NODISPLAY);
	time_Re_trapdoor = pbc_get_time() - time_Re_trapdoor;
	
	printf("\nRe-Trapdoor Generation Time: %0.3f ms \n", (time_Re_trapdoor) * 1000);
	
	double time_searching;
	time_searching = pbc_get_time();
	
	PRAEK_Fast_Search("Fast Searching: \n", FastSearchingIndex, RTrapdoor, isDisp);
	
	time_searching = pbc_get_time() - time_searching;
	
	printf("\nFast Searching Time: %0.3f ms \n\n", (time_searching) * 1000);
	
	
	return 0;
}