#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "binary.h"

void print_truth_table (unsigned char *output, unsigned int nargs, unsigned int nlines);
void print_dash_line(unsigned int nargs);
void print_pairs(unsigned int *pairs, unsigned int nargs);
void print_tests(unsigned int *tests, unsigned int ntests, unsigned int nargs, unsigned char *output);

#endif /* PRINT_H */
