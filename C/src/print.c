#include "print.h"


void print_dash_line(unsigned int nargs){
	int i=0;
	for(i=0; i<8*(nargs+4); i++)
		putchar('-');
	putchar('\n');
	fflush(stdout);
}


void print_truth_table (unsigned char *output, unsigned int nargs, unsigned int nlines){
	unsigned char *input = (unsigned char *) malloc(nargs*sizeof(unsigned char));
	unsigned int i, j;

	print_dash_line(nargs);

	printf("i\t|\t");
	for(i=0; i<nargs; i++){
		printf("%d\t", i);
	}
	printf("|\to\n");

	print_dash_line(nargs);

	for(i=0; i<nlines; i++){
		printf("%d\t|\t", i);
		decimal_to_binary(i, input, nargs);
		for(j=0; j<nargs; j++){
			printf("%u\t", input[j]);
		}
		printf("|\t%u\n", output[i]);
	}

	print_dash_line(nargs);

	free((unsigned char *) input);
	fflush(stdout);
	return;
}


void print_pairs(unsigned int *pairs, unsigned int nargs){
	unsigned int i;

	printf("Pairs:\n");
	for(i=0; i<nargs; i++){
		printf("(%d, %d) \t", pairs[2*i], pairs[2*i+1]);
	}
	printf("\n");

	fflush(stdout);
	return;
}


void print_tests(unsigned int *tests, unsigned int ntests, unsigned int nargs, unsigned char *output){
	unsigned char *input = (unsigned char *) malloc(nargs*sizeof(unsigned char));
	unsigned int i, j, test;

	printf("\nSolution: %d tests\n", ntests);
	print_dash_line(nargs);

	printf("i\t|\t");
	for(i=0; i<nargs; i++){
		printf("%d\t", i);
	}
	printf("|\to\n");

	print_dash_line(nargs);

	for(i=0; i<ntests; i++){
		test = tests[i];
		printf("%d\t|\t", test);
		decimal_to_binary(test, input, nargs);
		for(j=0; j<nargs; j++){
			printf("%u\t", input[j]);
		}
		printf("|\t%u\n", output[test]);
	}

	print_dash_line(nargs);

	free((unsigned char *) input);

	fflush(stdout);
	return;
}
