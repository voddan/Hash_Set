/*
 * This file tests the speed of constractions, 
 * developed in hash_set.c
 * 
 * I am using gcc -g and valgrind (cachegrind)
 **/
 
#include <stdio.h>
#include <string.h>

#include "hash_set.h"

#define ARRAY_LEN 150
type_t array[ARRAY_LEN] = {};

#define BUFFER_LEN 20
#define SPEED_TEST_LOOP 100000
 
int main() {
	//--------------------------------------------------------------
	printf("started working..\n");
	
	Hash_Set* set = Hash_Set_New();
	FILE* input = fopen("input.txt", "r");
//--------------------------------------------------------------
	printf("downloading..\n");
	for(int i = 0; i < ARRAY_LEN; i++) {
		char* buf = malloc(sizeof(char) * BUFFER_LEN);
		char* succeed = fgets(buf, BUFFER_LEN, input);
		
		if(!succeed) { // if no string
			printf( "#! The input file is too short\n"
				"#! It is just %d lines long, \n"
				"#! while we would expect more than %d lines\n"
				"#! Please rerun the program with another input file\n",
				i, ARRAY_LEN);
			return 1;
		}
		
		char* eol = strstr(buf, "\n");
		if(eol) *(eol) = '\0';
		
		array[i] = buf;
	}
//--------------------------------------------------------------
	for(int i = 0; i < ARRAY_LEN; i++) {
		Hash_Set_add(set, array[i]);
	}
//--------------------------------------------------------------
	Hash_Set_Dump(set);
	
	
//--------------------------------------------------------------
	printf("speed testing..\n");
	
	for(int j = 0; j < SPEED_TEST_LOOP; j++) {
		for(int i = 0; i < ARRAY_LEN; i++) {
			Hash_Set_find(set, array[i]);
		}
	}
	printf("speed testing is finished\n");
//--------------------------------------------------------------

	fclose(input);
	Hash_Set_Del(set);
	
	for(int i = 0; i < ARRAY_LEN; i++) {
		free(array[i]);
	}
	
	return 0;
}

