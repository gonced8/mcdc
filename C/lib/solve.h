#ifndef SOLVE_H
#define SOLVE_H

#include <stdlib.h>
#include <stdbool.h>

#include "binary.h"
#include "bubblesort.h"
#include "print.h"

typedef unsigned char (*Function) (unsigned char *);

typedef enum sol{ False='f', True='t', End='e'} Status;

void decimal_to_binary(unsigned int decimal, unsigned char *binary, unsigned int size);
unsigned char *get_output(Function function, unsigned int nargs, unsigned int nlines);
int find_solution (unsigned int nargs, unsigned int nlines, unsigned char *output);
void first_pair(unsigned int *pair, unsigned int nargs, unsigned int i);
unsigned int next_pair(unsigned int *pairs, unsigned int nargs, unsigned int nlines);
unsigned int next_pair_i(unsigned int *pairs, unsigned int nargs, unsigned int nlines, unsigned int i);
bool check_jump(unsigned int n, unsigned int nargs, unsigned int i);
unsigned int check_equal_output(unsigned int *pairs, unsigned int nargs, unsigned char *output);
unsigned int check_invalid_pairs(unsigned int *pairs, unsigned int nargs, unsigned int nlines, unsigned char *output);
unsigned int count_unique(unsigned int *pairs, unsigned int nargs);
Status check_solution(unsigned int *pairs, unsigned int nargs, unsigned int *saved_pairs, unsigned int *saved_ntests);
unsigned int filter_repeated_pairs(unsigned int *pairs, unsigned int nargs, unsigned int *saved_pairs);

#endif /* SOLVE_H */
