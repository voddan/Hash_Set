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
////////////////////////////////////////////////////////////////////////

const type_t* Hash_List_find(Hash_List* list, const type_t item) {
	char* str = (char*) item;
	type_t* result;
	
	
	__asm__ volatile (
		// rdi -> struct
		// rsi -> str
		
		"	movq %%rsi, %%r9			\n"
		// r9 -> str (begin)                          
		"	movq %%rdi, %%rax			\n"
		// rax -> struct                               
		"	cld					\n"
		                                               
		/////////////////                              
		"	movq (%%rdi), %%rdx			\n"
		// rdx == list->link
		"	orq %%rdx, %%rdx			\n"
		// if rdx == null                            
		"	jz _return				\n"
		// return 0                                     
		/////////////////                               
		                                               
		"_big_loop:					\n"
		                                               
		/////////////////                              
		"	movq %%r9, %%rsi			\n"
		// rsi -> str (begin)                           
		"	addq $8, %%rax				\n"
		"	movq (%%rax), %%rdi			\n"
		// rdi -> (struct->val)                         
		// not shure !!!!                               
		                                                
		"_cmp_loop:					\n"
		"	cmpb $0, (%%rsi) 			\n"
		"	jz _eol					\n"
			// slow jamp
		"	cmpsb					\n"
		"	je _cmp_loop				\n"
		                                              
		                                              
		// (rdi) != (rsi)                             
		"	movq %%rdx, %%rax			\n"
		// list := list->link;                     
		"	movq (%%rax), %%rdx			\n"
		// rdx := list->link                          
		"	orq %%rdx, %%rdx			\n"
		// if rdx == null                             
		"	jnz _big_loop				\n"
		// return 0                                  
		"						\n"
		"_return:					\n"
		"	xorq %%rax, %%rax			\n"
		// return 0                                   
		"_eol:						\n"
		// (rdi) == 0
	:"=a"(result) 		// fixed // -> string
	:"D"(list), "S"(str) 	// fixed
	: "rbx", "r9", "rdx"
	);
	
	return result;
}

//optimazed with ASM
// works only with strings
const type_t* Hash_List_find_3(Hash_List* list, const type_t item) {
	char* str = (char*) item;
	type_t* result;
	
	
	__asm__ volatile (
		// rdi -> struct
		// rsi -> str
		
		"	movq %%rsi, %%r9						\n"
		// r9 -> str (begin)
		"	movq %%rdi, %%r8						\n"
		// r8 -> struct
		"	cld						\n"
		
		/////////////////
		"big_loop:						\n"
		"	movq (%%r8), %%rdx						\n"
		// rdx == list->link
		"	xorq %%rax, %%rax					\n"
		// rax := 0
		// then return 0
		"	orq %%rdx, %%rdx						\n"
		// is rdx 0?
		"	jz return						\n"
		// return if !rdx
		/////////////////
		
		
		
		/////////////////
		"	movq %%r9, %%rsi						\n"
		// rsi -> str (begin)
		"	addq $8, %%r8						\n"
		"	movq (%%r8), %%rdi						\n"
		// rdi -> (struct->val)  
		// not shure !!!!
		
		// work bad with empty lines
		"cmp_loop:						\n"
		"	cmpb $0, (%%rsi) 						\n"
		"	jz eol						\n"
		"	cmpsb						\n"
		"	je cmp_loop						\n"
		// (rdi) != (rsi)
		// list := list->link;
		"	movq %%rdx, %%r8						\n"
		"	jmp big_loop						\n"
		"							\n"
		"							\n"
		"eol:						\n"
		// (rdi) == 0
		//"	addq $8, %%r8						\n"
		"	movq %%r8, %%rax						\n"
		"							\n"
		"return:						\n"
		"							\n"
	:"=a"(result) 		// fixed // -> string
	:"D"(list), "S"(str) 	// fixed
	: "rbx", "r8", "r9", "rdx"
	);
	
	/*
	while(list->link) {
		if (item == list->value)
			return &(list->value);
		else
			list = list->link;
	}
	*/
	
	/*
	typedef struct Hash_List {
		struct Hash_List* link;
		type_t value;
	} Hash_List;
	*/
	
	return result;
}

const type_t* Hash_List_find_2(Hash_List* list, const type_t item) {
	//assert(list);
	
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

