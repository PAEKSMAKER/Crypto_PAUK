/*
 * UFPAEK.c
 *
 *  Created on: 2022-07-04
 * 
 *      Author: kir
 *
 * 		Algorithms of Updatable FS-PAEKS scheme.
 * 
 * */
 
#include "UFPAEK.h"

//====KeyGen_user Algorithm of Updatable FS-PAEKS scheme====
//
//KeyGen_user(pp): pk = {pk_X1, pk_X1} = {g^sk_x1, g^sk_x2}, sk = {sk_x1, sk_x2};
//
int UFPAEK_keygen_user(element_t G1_pk_X1, element_t G1_pk_X2 , element_t Zr_sk_x1, element_t Zr_sk_x2) {
	
	keygen( G1_pk_X1 ,  Zr_sk_x1 ) ;
	keygen( G1_pk_X2 ,  Zr_sk_x2 ) ;
	
	return 0;
}


int UFPAEK_keygen_server(element_t G1_pk_Z, element_t Zr_sk_z) {
	
	keygen( G1_pk_Z ,  Zr_sk_z ) ;
	
	return 0;
}


//====Encrypt algorithm of Updatable FS-PAEKS scheme====
unsigned char* UFPAEK_encrypt(char* displayMsg, char *msg, element_t pk_Y1, element_t pk_Y2, 
					element_t sk_x1, element_t sk_x2, int isDisp){
	
	
	
	
	}



//====Trapdoor algorithm of Updatable FS-PAEKS scheme====



//====Test algorithm of Updatable FS-PAEKS scheme====



//====Update algorithm of Updatable FS-PAEKS scheme====


