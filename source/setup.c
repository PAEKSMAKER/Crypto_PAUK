/*
 * 	setup.c
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

#include"setup.h"

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


int keygen(element_t public_key, element_t security_key) {
	element_init_G1(public_key, pairing);
	element_init_Zr(security_key, pairing);
	element_random(security_key);
	
	element_pow_zn(public_key, generator, security_key);
	return 0;
}
