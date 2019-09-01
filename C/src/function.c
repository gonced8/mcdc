#include "function.h"

unsigned int nthreads = 4;
unsigned char show_truth_table = 0;
unsigned int nargs = 6;

unsigned char function (unsigned char input[]){
	return (unsigned char) ((input[0] & input[1]) ^ (input[2] & input[3]) ^ (input[4] & input[5]));
}


unsigned int get_nthreads(void){
	return nthreads;
}

unsigned char get_show_truth_table(void){
	return show_truth_table;
}

unsigned int get_nargs(void){
	return nargs;
}
