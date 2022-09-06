/*
 * 	com_Algorithm.c
 *
 *  	Created on: 2015-1-23
 *      	Author: kir
 *		
 * 		Setup the bilinear pairing based cryptosystem.
 * 		Read the global parameter from the file "a.param" to initialize the bilinear pairing map.
 * 		The bilinear pairing map used here is symmetric.
 * 
 * 		Read the pre-set generator, which is randomly picked from group G_1, and set "len1" to be the length of the generator.
 * 		
 * 		//len1 : length of generator in G1
 * 		//len2: length of generator in GT
 * 
 * 		*/

#include"common.h"

int setup(int isDispPP, int isDispGenerator) {

	char param[1024] = { '\0' };
	FILE *stream, *streamG; //stream 是公共参数文件， streamG 是generator文件
	char filenameParam[] =
			"../param/a.param";
	char filenameGenerator[] =
			"../param/generator.bin";

	if ((stream = fopen(filenameParam, "r")) == NULL) { //input pairing param
		fprintf(stderr, "Cannot open input file.\n");
		return 1;
	}
	fseek(stream, 0, SEEK_SET);
	fread(param, 1, 1024, stream);
	if(isDispPP){
		printf("%s\n\n", param);
	}
	fclose(stream);

	pairing_init_set_str(pairing, param); //初始化参数

	element_init_G1(generator, pairing);
	element_random(generator);	
	len1 = element_length_in_bytes(generator); //len1 : length of generator in G1
	
	element_t GT_tmp;
	element_init_GT(GT_tmp, pairing);
	len2 = element_length_in_bytes(GT_tmp);	//len2: length of generator in GT

	char *tmpGenerator = malloc(len1 * 2 * sizeof(char));
	unsigned char *tmpUnsignedGenerator = malloc(len1 * sizeof(unsigned char));
	if ((streamG = fopen(filenameGenerator, "r")) == NULL) {
		fprintf(stderr, "Cannot open input file: read generator error.\n");
	}
	fseek(streamG, 0, SEEK_SET);
	fread(tmpGenerator, sizeof(char), len1 * 2, streamG);
	fclose(streamG);
	tmpUnsignedGenerator = hexToStr(tmpGenerator, len1);
	element_from_bytes(generator, tmpUnsignedGenerator);
	
	if(isDispGenerator){
			
		printUnsignedChar("Generator:\n", tmpUnsignedGenerator, len1);
	
		printf("len1 = %d\n", len1);
		printf("len2 = %d\n", len2);
	}
	
	
	free(tmpGenerator);
	free(tmpUnsignedGenerator);

	return 0;
}

int setupF(){	//Type F bilinear pairing; It is suitable for schemes without pairing, there is no pairing from G1*G1 -> GT
						// The only pairing is from G1 * G2 -> GT 
	
	
	
	
	
	return 0;
}


int keygen(element_t public_key, element_t security_key) {
	element_init_G1(public_key, pairing);
	element_init_Zr(security_key, pairing);
	element_random(security_key);
	
	element_pow_zn(public_key, generator, security_key);
	return 0;
}



int SenderEnroll(char* displayMsg, int Enroll_num, element_t *pkSenders, element_t * skSenders, int isDisp){
	
		int i;
		for(i = 0; i < Enroll_num; i++){
			element_init_Zr(skSenders+ i, pairing);
			element_random(skSenders+i);
			if(isDisp)
			element_printf("%B\n", skSenders+i);
		}
		
		
		for(i = 0; i < Enroll_num; i++){
			element_init_G1(pkSenders+ i, pairing);
			PAEKS_keygen(pkSenders + i, skSenders + i);
			if(isDisp)
			element_printf("%B\n", pkSenders+i);
		}
	}

int random_sender(int startNum, int endNum){
	int random_sender_num;
	int num_of_senders = endNum - startNum;
	
	double time_seed = pbc_get_time();
	random_sender_num = (int)(time_seed * 10000000) % num_of_senders + startNum;
	
	return random_sender_num;
}

int random_num(int total_num, int startNum){
	int random_num;
	
	double time_seed = pbc_get_time();
	random_num = 	(int) (time_seed * 1000000) % total_num + startNum;
	
	return random_num;
}
