/*
 * PAEKS_keyGen.c
 *
 *  Created on: 2021-09-28
 * 
 *      Author: kir
 *
 * 		Implement the KeyGen algorithm in PAEKS scheme.
 * 		Input:	 	public parameter (pp).	
 * 		Output:	 public/secret key pairing (pk/sk).
 * 
 * 		Same as the keyGen algorithm in Setup.c
 * 
 * */


#include"PAEKS_main.h"



int PAEKS_keygen(element_t public_key, element_t security_key) {
	
	keygen( public_key,  security_key) ;
	
	return 0;
}