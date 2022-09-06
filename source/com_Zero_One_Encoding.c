/*
 * com_Zero_One_Encoding.c
 *
 *  Created on: 2022-6-27
 *      Author: kir
 */

#include "common.h"
#include "time.h"




theSet *createTheSet(){	// create an empty set
	theSet *head;
	head = (theSet*)malloc(sizeof(theSet));
	head->data = 0;	// the counter of the link will be stored in the head node.
	head->next = NULL;
	return head;
}

theSet *createNode(int inputData){	// given an integer (inputData), generate an element, which will be added into the set.
	theSet *node;
	node = (theSet*)malloc(sizeof(theSet));
	node->data = inputData;
	node->next = NULL;
	return node;
}

theSet *addNode(theSet *head, int inputData){	// add an integer into the set.
	head->data++;
	theSet *tmp = head->next;
	head->next = createNode(inputData);
	head->next->next = tmp;
	return head;
}

void print_theSet(theSet *head){
	theSet *tmp = head;
	int i = head->data;
	while(i-- && tmp->next){
		tmp = tmp->next;
		printf("%d ", tmp->data);
	}
	printf("\n");
	return;
}

int *findSameElement(theSet *theZeroSet, theSet *theOneSet){
	
	int elementsLeft_Zero = theZeroSet->data;
	int elementsLeft_One = theOneSet->data;
	
	int *counter =  malloc(sizeof(int) * 2);		// the counter: the position of the same elements in the 0-set and 1-set.
	counter[0] = 1;
	counter[1] = 1;
	
	theSet *tmp_Zero = theZeroSet->next;
	theSet *tmp_One = theOneSet->next;
	
	while(elementsLeft_Zero && elementsLeft_One){// the two sets must be sorted in ascending order
		if(tmp_Zero->data == tmp_One->data){
			return counter;
		}//End if
		else if(tmp_Zero->data < tmp_One->data){
			tmp_Zero = tmp_Zero->next;
			elementsLeft_Zero--;
			counter[0]++;
		}//End else if
		else{
			tmp_One = tmp_One->next;
			elementsLeft_One--;
			counter[1]++;
		}//End else
	}//End while
	
	counter[0] = 0;		// if there is no element of Zero equal to any element of One, set counter as {0, 0}, which means no matching.
	counter[1] = 0;
	
	return counter;
}
	
	
theSet *zero_Encoding(int time_input){ //ZeroEncoding with input t = time_input
	
	int tmp_time_point = time_input;
	theSet *theSetFromZeroEncoding = createTheSet();
	
	while(tmp_time_point){// the length of the timepoint must be the same as that in ONE_ENCODING function
		if(tmp_time_point%2 == 0){
			tmp_time_point++;
			addNode(theSetFromZeroEncoding, tmp_time_point);
//			printf("%d ", tmp_time_point);
		}
		tmp_time_point = tmp_time_point>>1;
	}
	
	printf("Zero Encoding: ");
	print_theSet(theSetFromZeroEncoding);
	return theSetFromZeroEncoding;
}


theSet *one_Encoding(int time_input){ //OneEncoding with input t = time_input +1 (Here is different from zero_Encoding)
	
	int tmp_time_point = time_input+1;
	
	theSet *theSetFromOneEncoding = createTheSet();
	
	while(tmp_time_point){// the length of the timepoint must be the same as that in ZERO_ENCODING function
		if(tmp_time_point%2 == 1){
			addNode(theSetFromOneEncoding, tmp_time_point);
//			printf("%d ", tmp_time_point);
		}
		tmp_time_point = tmp_time_point>>1;
	}
	
	printf("One Encoding: ");
	print_theSet(theSetFromOneEncoding);
	return theSetFromOneEncoding;
}
	
	
void getTimePoint_Info(){
	
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf ( "\007The current date/time is: %s", asctime (timeinfo) );
	getTimePoint_Second(1);
	getTimePoint_Minute(1);
	getTimePoint_Hour(1);
	getTimePoint_Day(1);
	getTimePoint_Month(1);
	getTimePoint_Year(1);
	return;
}

	
int getTimePoint_Second(int isDisplay){
	
	time_t rawtime;
	time ( &rawtime );
	int result_second = rawtime;
	if(isDisplay)
		printf("The current time_second is: %d\n", result_second); //seconds
	return (result_second);
}
	
int getTimePoint_Minute(int isDisplay){
	
	int result_minute = getTimePoint_Second(0)/60;
	if (isDisplay)
		printf("The current time_minute is: %d\n", result_minute); //minutes
	return result_minute;
}

int getTimePoint_Hour(int isDisplay){
		
	int result_hour = getTimePoint_Minute(0)/60;
	if(isDisplay)
		printf("The current time_hour is: %d\n", result_hour); //hours
	return result_hour;
	}
	
int getTimePoint_Day(int isDisplay){
	
	int result_day = getTimePoint_Hour(0)/24;
	if(isDisplay)
		printf("The current time_day is: %d\n", result_day); //days
	return result_day;
}

int getTimePoint_Month(int isDisplay){
	
	int result_month = getTimePoint_Day(0)/31;
	if(isDisplay)
		printf("The current time_month is: %d\n", result_month); //months
	return result_month;
}

int getTimePoint_Year(int isDisplay){
	
	int result_year = getTimePoint_Day(0)/365;
	if(isDisplay)
		printf("The current time_year is: %d\n", result_year); //years
	return result_year;
}