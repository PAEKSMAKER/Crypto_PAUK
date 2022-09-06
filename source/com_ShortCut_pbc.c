




#include "common.h"

void Random_G1(eleG1 g, pairing_t pairing){
	element_init_G1(g, pairing);
	element_random(g);
}

void Random_G2(eleG2 g, pairing_t pairing){
	element_init_G2(g, pairing);
	element_random(g);
}

void Random_GT(eleGT egg, pairing_t pairing){
	element_init_GT(egg, pairing);
	element_random(egg);
}
	
void Random_Zr(eleZr e, pairing_t pairing){
	element_init_Zr(e, pairing);
	element_random(e);
}

void print_element(char* displayMsg, element_t  e){
	int i = 0;
	int len_dispMsg = (int) strlen(displayMsg);
	for (i = 0; i < len_dispMsg; i++){
		printf("%c", displayMsg[i]);
	}
	element_printf("%B", e);
	printf("\n");
}