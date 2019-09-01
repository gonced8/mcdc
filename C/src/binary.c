#include "binary.h"


void decimal_to_binary(unsigned int decimal, unsigned char *binary, unsigned int size){
	int i;
	for(i=0; i<size; i++){
		binary[i] = (unsigned char) ((decimal>>(size-i-1)) & 1);
	}

	return;
}
