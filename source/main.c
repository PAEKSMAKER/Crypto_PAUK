#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/crypto.h>
#include <openssl/sha.h>
#include "common.h"
#include "PAEKS.h"
#include "PRAEK.h"
#include "time.h"


int main()
{	
	double time_setup;
		
	time_setup = pbc_get_time();
	
	
	
	setup(NODISPLAY, NODISPLAY);
	time_setup = pbc_get_time() - time_setup;
	
	printf("Setup time: %03f ms\n", time_setup * 1000);
	//SENDER_NUM = 100;
	
	element_t skSenders[SENDER_NUM]; 
	element_t pkSenders[SENDER_NUM];
	SenderEnroll("Enroll Senders: \n", SENDER_NUM, pkSenders, skSenders, NODISPLAY);
	
	char * dictionary = malloc(MAX_LEN_DIC);
	inputMessage_fromfile("\nDictionary:\n", dictionary, MAX_LEN_DIC, "../param/dictionary.txt", NODISPLAY);
	
	PEKSkeyword  keywords[100] = {'0'};
	int keyword_num = kwReadDictionary("Keywords read form Dictionary: \n", keywords, dictionary, NODISPLAY);
	
	
	int num_of_ciphers = 30;
	int num_of_senders = 25;
	
	
	char * PAEKS_dispMsg = "========== P A E K S ==========\n";
	char * PRAEK_dispMsg = "========== P R A E K ==========\n";
	
	printf("Num of Ciphertexts: %d \n", num_of_ciphers);
	printf("Num of Senders: %d \n", num_of_senders);
	
    PAEKS_main(PAEKS_dispMsg, keywords, num_of_ciphers, num_of_senders,  keyword_num, pkSenders, skSenders, NODISPLAY);
	
	PRAEK_main(PRAEK_dispMsg, keywords, num_of_ciphers, num_of_senders,  keyword_num, pkSenders, skSenders, NODISPLAY);
	
	
	
	
	
	return 0;
}




