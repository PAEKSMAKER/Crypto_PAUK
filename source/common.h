/*
 * common.h
 *
 *  Created on: 2021-10-15
 *      Author: kir
 */

#include"/usr/local/include/pbc/pbc.h"
#include"/usr/local/include/pbc/pbc_test.h"
#include<string.h>
#include<openssl/crypto.h>
#include<openssl/sha.h>

#define DISPLAY 1
#define NODISPLAY 0
#define TRUE 1
#define FALSE 0
#define MAX_MSG_LEN 64
#define MAX_LEN_DIC 5000
#define MAX_KW_LEN 25
#define MAX_NUM_OF_KW 400
#define SENDER_NUM 100
#define GROUPTYPE_G1 1
#define GROUPTYPE_G2 2
#define GROUPTYPE_GT 3

#ifndef COMMON_H_
#define COMMON_H_

typedef  element_t eleG1;
typedef  element_t eleG2;
typedef  element_t eleGT;
typedef  element_t eleZr;

typedef char PEKSkeyword[MAX_KW_LEN+2]; 
typedef char PEKSdictionary[MAX_NUM_OF_KW][MAX_KW_LEN+2];
 

pairing_t pairing;
element_t generator;


int len1, len2;

int change();

//====com_Algorithm====
int setup(int isDispPP, int isDispGenerator);
int keygen(element_t public_key, element_t security_key);
int SenderEnroll(char* displayMsg, int Enroll_num, element_t * pkSenders, element_t * skSenders, int isDisp);

//====com_IO====
int inputMessage_fromfile(char* displayMsg, char * msg, int len, char * filename_msg, int isDisp);
int printUnsignedChar(char * displayMsg, unsigned char * ustr_msg, int len_msg);
int printString(char*displayMsg, char *msg, int isDispLength);

int kwAssign(PEKSkeyword kw, char* chars);
int kwAssign_withLength(PEKSkeyword kw, char* chars, int len_chars);
int kwReadDictionary(char* displayMsg, PEKSkeyword *keywords, char* dictionary, int isDisp);
int kwLength(PEKSkeyword kw);
int kwPrint(char* displayMsg, PEKSkeyword kw);

//
 
//====com_StringOperation====
int ustrCMP(unsigned char *str1, unsigned char *str2, int length);
unsigned char *XOR(unsigned char *m, unsigned char* gr, int len);
unsigned char *hash1(unsigned char *msg, int msgLength);
unsigned char *hash2(unsigned char *msg, int msgLength);

char *strToHex(unsigned char *str, int length);
unsigned char *hexToStr(char *hex, int length);

int random_sender(int startNum, int endNum);
int random_num(int total_num, int startNum);




//====com_Zero_One_Encoding====

typedef struct linkArray{
	int data;			//
	struct linkArray *next;		//
}theSet;

theSet *createTheSet();
theSet *createNode(int inputData);
theSet *addNode(theSet *head, int inputData);
void print_theSet(theSet *head);
int *findSameElement(theSet *theZeroSet, theSet *theOneSet);
theSet *zero_Encoding(int time_input);
theSet *one_Encoding(int time_input);
void getTimePoint_Info();
int getTimePoint_Second(int isDisplay);
int getTimePoint_Minute(int isDisplay);
int getTimePoint_Hour(int isDisplay);
int getTimePoint_Day(int isDisplay);
int getTimePoint_Month(int isDisplay);
int getTimePoint_Year(int isDisplay);
 
#endif /* COMMON_H_ */