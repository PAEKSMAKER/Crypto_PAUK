/*
 * 	com_IO.c
 *
 *  	Created on: 2021-09-29
 *      	Author: kir
 *		
 * 		print unsigned char type strings to the screem		
 * 		
 * 		*/
 
 #include "common.h"
 
 //====OUTPUT====
 
int printUnsignedChar(char * displayMsg, unsigned char * ustr_msg, int len_msg){
	
	int i = 0;
	int len_dispMsg =  (int) strlen(displayMsg);
	for (i = 0; i < len_dispMsg; i++){
		printf("%c", displayMsg[i]);
	}
	
	for (i = 0; i < len_msg; i++) {
		printf("%02X", ustr_msg[i]);
	}
	printf("\n");
	
	return 0;
}

int printString(char*displayMsg, char *msg, int isDispLength){
	int i = 0;
	int len_dispMsg = (int) strlen(displayMsg);
	for (i = 0; i < len_dispMsg; i++){
		printf("%c", displayMsg[i]);
	}
	printf("%s\n", msg);
	//printf("\n");
	if(isDispLength){
		printf("Length of Msg: %d \n",  (int) strlen(msg));
	}
	
	return 0;
	}
	
	//====INPUT====
	
	int inputMessage_fromfile(char* displayMsg, char * msg, int len, char * filename_msg, int isDisp){
	
	int i;
	for (i = 0; i < len; i++){
		msg[i] = '\0';
		}
	
	FILE *streamM;
	if ((streamM = fopen(filename_msg, "r+")) == NULL)
		fprintf(stderr, "Cannot open input file: Msg1\n");
	
	fread(msg, sizeof(char), len, streamM);
	fclose(streamM);
	
	if(isDisp){
		printString(displayMsg, msg, DISPLAY);
	}
	
	return 0;
	}
 
 //====Keyword Input & Operation====
 
 int kwAssign(PEKSkeyword kw, char* chars){
	 
	 int i;
	 if(strlen(chars) > MAX_KW_LEN){
		 kw[0] = MAX_KW_LEN;
	 }
	 else{
		 kw[0] = strlen(chars);
	 }//end if-else
	 
	 for(i = 1; i <= kw[0]; i++){
		 kw[i] = *(chars + i - 1);
		 kw[i+1] = '\0';
	 } 
	 return 0;
 }
 
  
 int kwAssign_withLength(PEKSkeyword kw, char* chars, int len_chars){
	 
	 int i;
	 if(strlen(chars) < len_chars){
		 kw[0] = strlen(chars) ;
	 }
	 else{
		 kw[0] = len_chars;
	 }//end if-else
	 
	 for(i = 1; i <= kw[0]; i++){
		 kw[i] = *(chars + i - 1);
	 }
	 
	 return 0;
 }
 
 int kwEmpty(PEKSkeyword kw){
	 if(kw[0] == 0){
		 return TRUE;
	 }
	 else{
		 return FALSE;
	 }
 }
 
 int kwCompare(PEKSkeyword kw1, PEKSkeyword kw2){
	 
	 int i ;
	 for(i = 1; i <= kw1[0] && i <= kw2[0]; ++i){
		 if(kw1[i] != kw2[i])
			 return kw1[i] - kw2[i];
	 }
	 return kw1[0] - kw2[0];
 }
 
 
 int kwReadDictionary(char* displayMsg, PEKSkeyword *keywords, char* dictionary, int isDisp){
	 
	
	int i, j;
	int kw_num = 0;
	int startPointer = 0;
	int len_kw = 0;
	
	if (isDisp){
		int len_dispMsg = (int) strlen(displayMsg);
		for (i = 0; i < len_dispMsg; i++){
			printf("%c", displayMsg[i]);
		}
	}
	
	
	for (i = 0; i < MAX_NUM_OF_KW; i++){
		len_kw = 0;
		for(j = 0; j < MAX_KW_LEN; j++){
			if(dictionary[startPointer + j] == ' ' || dictionary[startPointer + j] == '\n' || dictionary[startPointer + j] == '\0'){
				break;
			}	//end if
		} //end for j
		
		len_kw = j;
		
		if(len_kw == 0){
			startPointer++;
			continue;
		}	
		
		keywords[kw_num][0] = len_kw;
		
		kwAssign_withLength(keywords[kw_num] , dictionary+ startPointer, len_kw);
		
		if(isDisp){
			kwPrint("Keyword: ", keywords[kw_num] );
			printf("Length: %d\n", len_kw);
		}
		
		kw_num++;
		startPointer += len_kw;
		
		if( strlen(dictionary) <= startPointer)
			break;
		
	}
	 
	 return kw_num;
 } 
 
	int kwLength(PEKSkeyword kw){
		return kw[0];
	}		
	
	int kwPrint(char* displayMsg, PEKSkeyword  kw){
		int i;
		int len_dispMsg = (int) strlen(displayMsg);
		for (i = 0; i < len_dispMsg; i++){
		printf("%c", displayMsg[i]);
	}
		for(i = 1; i <= kw[0]; i++){
			printf("%c", kw[i]);
		}
		printf("\n");
		
		return 0;
	}
	
 