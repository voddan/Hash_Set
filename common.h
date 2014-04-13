 /*
 * Common constants and functions 
 * for realiasation of Hash_Set and Hash_List
 **/
 
#ifndef _COMMON_H_
#define _COMMON_H_
 
typedef char* type_t;
#define HASH_SET_LEN 15

#include <assert.h>

#define abs(x) (((x) >= 0) ? (x) : (-(x)))

/*
int _hash_func(type_t item) {
	int res = abs((int) item) % (HASH_SET_LEN);
	
	assert(0 <= res && res < HASH_SET_LEN);
	return res;
} */

int _hash_func(type_t item) {
	int res = *((unsigned*) item) % (HASH_SET_LEN);
	
	assert(0 <= res && res < HASH_SET_LEN);
	return res;
}



#endif // _COMMON_H_
