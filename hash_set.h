/*
 * Defenition of hash_set 
 **/
#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "hash_list.h"

typedef struct Hash_Set {
	Hash_List* table[HASH_SET_LEN];
	
} Hash_Set;

Hash_Set* Hash_Set_New() {
	Hash_Set* set = (Hash_Set*) malloc(sizeof(Hash_Set));
	assert(set);
	
	for (int i = 0; i < HASH_SET_LEN; i++) {
		set->table[i] = Hash_List_New((type_t) 0); // takes memory
		//set->table[i] = NULL;
	}
	return set;
}

void Hash_Set_Del(Hash_Set* set) {
	if(!set) return;
	for (int i = 0; i < HASH_SET_LEN; i++) {
		Hash_List_Del( set->table[i] );
		set->table[i] = NULL;
	}
	free(set);
}

void Hash_Set_Dump(const Hash_Set* set) {
	printf("------------\n");
	printf("Hash_Set(%d)\n", HASH_SET_LEN);
	
	if(!set) {
		printf("--null--\n");
		return;
	}
	
	for (int i = 0; i < HASH_SET_LEN; i++) {
		printf("  %2d: ", i);
		Hash_List_Dump( set->table[i] );
	}
	
	printf("---\n");
}


//----------------------------------------------------------------------
void Hash_Set_add(const Hash_Set* set, type_t item) {
	assert(set);
	
	int hash = _hash_func(item);
	
	Hash_List_add(set->table[hash], item);
}

const type_t* Hash_Set_find(const Hash_Set* set, type_t item) {
	assert(set);
	
	int hash = _hash_func(item);
	
	return Hash_List_find(set->table[hash], item);
}
