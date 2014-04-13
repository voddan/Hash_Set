/*
 * This is an exapmle of implementation of a hash set.
 * 
 * The main task is to find out the most critical part of the program
 * and to optimase it with ASM language.
 * 
 * Recomended profilers are: valgrind, prof
 * 
 * Functionality:
 * 	1) remembers a number (int)
 * 	2) answers if there was such a number before
 * 
 * Note that it is an educational project, so the main goals are:
 * 	Simplicity
 * 	Development time
 * 	Visibility
 * 
 * In particular I am going to block some gcc optimisations
 * in order to simplify the asm optimisation.
 * 
 **/
 
#include <stdio.h>

#include "hash_set.h"

#define ARRAY_LEN 9
type_t array[ARRAY_LEN] = {78, 54, -1, -2, 54, 48, 13, 5, 54};

 
int main() {
	printf("started working..\n");
	
	Hash_Set* set = Hash_Set_New();
	
	// Hash_Set_add
	for(int i = 0; i < ARRAY_LEN; i++) {
		Hash_Set_add(set, array[i]);
	}
	
	
	Hash_Set_Dump(set);
	
	// Hash_Set_find
	for(int i = 0; i < ARRAY_LEN; i++) {
		const type_t* t = Hash_Set_find(set, array[i]);
		printf("find(%2d): %p  (%d)\n", array[i], t, (t)? *t : 0);
	}
	
	// Hash_Set_find (random)
	printf("--random--\n");
	for(int i = 0; i < 10; i++) {
		const type_t* t = Hash_Set_find(set, i);
		printf("find(%2d): %p  (%d)\n", i, t, (t)? *t : 0);
	}
	
	
	Hash_Set_Del(set);
	
	return 0;
}

