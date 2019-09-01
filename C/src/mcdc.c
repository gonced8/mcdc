#include "mcdc.h"

int main(void){
	unsigned int nthreads = get_nthreads();
	unsigned char show_truth_table = get_show_truth_table();
	unsigned int nargs = get_nargs();
	unsigned int nlines = 1<<nargs;

	unsigned char *output = get_output(function, nargs, nlines);

	if (show_truth_table)
		print_truth_table(output, nargs, nlines);

	printf("Total # of tests = %d\n", nlines);

	solve_with_threads(nthreads, nargs, nlines, output);

	free((unsigned char *) output);

	printf("\nEND\n");
	return 0;
}
