/*
 * com_StringOperation.c
 *
 *  Created on: 2015-4-5
 *      Author: kir
 */

#include"common.h"


//====strTypeChange====

char valueToHex(unsigned char value) {
	char result = 0;
	if (value >= 0 && value <= 9)
		result = '0' + value;
	else if (value >= 10 && value <= 15)
		result = 'A' + value - 10;
	else
		printf("valueToHex ERROR\n");
	return result;;
}

char *strToHex(unsigned char *str, int length) {
	char *hex = malloc(length * 2 * sizeof(char));
	unsigned char tmp;
	char high, low;
	int i, j;
	for (i = 0, j = 0; i < length; i++) {
		tmp = str[i] >> 4;
		tmp = tmp & 15;
		high = valueToHex(tmp);
		low = valueToHex(str[i] & 15);
		hex[j++] = high;
		hex[j++] = low;
	}
	return hex;;
}
unsigned char valueToStr(char value) {
	unsigned char result = 0;
	if (value >= '0' && value <= '9')
		result = value - '0';
	else if (value >= 'A' && value <= 'F')
		result = value - 'A' + 10;
	else
		printf("valueToStr ERROR\n");
	return result;
}
unsigned char *hexToStr(char *hex, int length) {

	unsigned char *str = malloc(length * sizeof(unsigned char));

	unsigned char high, low;
	int i, j;
	for (i = 0, j = 0; i < length; i++) {
		high = valueToStr(hex[j++]);
		str[i] = high << 4;
		low = valueToStr(hex[j++]);
		str[i] += low;
	}
	return str;
}


//====Unsigned String CMP====

int ustrCMP(unsigned char *str1, unsigned char *str2, int length) {

	int unTrue = 0;
	int i;
	for (i = 0; i < length; i++) {
		if (str1[i] != str2[i]) {
			unTrue = 1;
			break;
		} //end if()
	} //end for()

	return unTrue;
}

//====Unsigned String XOR Operation====

unsigned char *XOR(unsigned char *m, unsigned char* gr, int len) {
	int i;
	unsigned char *result = (unsigned char*) malloc(
			len * sizeof(unsigned char));
	memset(result, 0, len);
	for (i = 0; i < len; i++) {
		result[i] = m[i] ^ gr[i];
	}
	return result;
}