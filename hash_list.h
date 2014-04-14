 /*
 * Defenition of hash_slist 
 **/
#include <stdlib.h>
#include <stdio.h>
 
#include "common.h"

typedef struct Hash_List {
	struct Hash_List* link;
	type_t value;
} Hash_List;
 
Hash_List* Hash_List_New(type_t value) {
	Hash_List* list = malloc(sizeof(Hash_List));
	assert(list);
	
	list->link = NULL;
	list->value = value;
	return list;
}

void Hash_List_Del(Hash_List* list) {
	if(!list) return;
	
	Hash_List_Del(list->link);
	
	free(list);
}

void Hash_List_Dump(const Hash_List* list) {
	// one line, '\n' in the end
	if(!list) {
		printf("--NULL--\n");
		return;
	}
	
	if(!list->link) {
		printf("END\n");
		return;
	}
	
	printf(" '%s', ", list->value);
	Hash_List_Dump(list->link);
}



//----------------------------------------------------------------------
// deletes the duplicates
void Hash_List_add(Hash_List* list, const type_t item) {
	assert(list);
	
	if(list->link){
		if(item == list->value) return;
			
		Hash_List_add(list->link, item); // very slow // but ok now
	} else {
		list->link = Hash_List_New((type_t) 0);
		list->value = item;
	}
}

const type_t* Hash_List_find(Hash_List* list, const type_t item) {
	assert(list);
	
	while(list->link) {
		if (item == list->value)
			return &(list->value);
		else
			list = list->link;
	}
	
	return 0;
}

// recursive implementation; was too slow
const type_t* Hash_List_find_1(const Hash_List* list, const type_t item) {
	assert(list);
	
	if(list->link) {
		if(item == list->value)
			return &(list->value);
		else
			return Hash_List_find(list->link, item);
	} else 
		return 0;
}

