#include "solve.h"

unsigned char *get_output(Function function, unsigned int nargs, unsigned int nlines){
	unsigned char *output;
	unsigned char *line;
	unsigned int i;

	output = (unsigned char *) malloc( nlines*sizeof(unsigned char) );
	line = (unsigned char *) malloc( nargs*sizeof(unsigned char) );

	for(i=0; i<nlines; i++){
		decimal_to_binary(i, line, nargs);
		output[i] = function(line);
	}

	free((unsigned char *) line);

	return output;
}


int find_solution (unsigned int nargs, unsigned int nlines, unsigned char *output){
	unsigned int i;
	unsigned int *pairs = (unsigned int*) malloc(2*nargs*sizeof(unsigned int));	
	unsigned int *saved_pairs = (unsigned int*) malloc(2*nargs*sizeof(unsigned int));	
	unsigned int saved_ntests = nargs*2+1;
	Status res;

	/* Initializing pairs array */
	for(i=0; i<nargs; i++){
		first_pair(pairs+2*i, nargs, i);
	}

	i = 0;
	while(i < nargs){
		i = check_invalid_pairs(pairs, nargs, nlines, output);

		res = check_solution(pairs, nargs, saved_pairs, &saved_ntests);

		if(res != False){
			print_tests(saved_pairs, saved_ntests, nargs, output);
			print_pairs(pairs, nargs);
		}
		if(res == End)
			break;

		i = next_pair(pairs, nargs, nlines);
	}

	free((unsigned int *) pairs);
	free((unsigned int *) saved_pairs);

	return 0;	
}


void first_pair(unsigned int *pair, unsigned int nargs, unsigned int i){
	pair[0] = 0;
	pair[1] = 1<<(nargs-i-1);

	return;
}


unsigned int next_pair(unsigned int *pairs, unsigned int nargs, unsigned int nlines){
	unsigned int i = nargs-1;
	unsigned int *x = pairs+2*(nargs-1);
	unsigned int *y = x+1;

	*x += 2;
	*y += 2;

	if (*x>=nlines){
		first_pair(x, nargs, nargs-1);
		return next_pair_i(pairs, nargs, nlines, i-1);
	}
	else{
		return i;	/* return index of changed pair */
	}
}


unsigned int next_pair_i(unsigned int *pairs, unsigned int nargs, unsigned int nlines, unsigned int i){
	unsigned int *x = pairs+2*i;
	unsigned int *y = x+1;

	if(i>=nargs)
		return nargs;

	if(check_jump(*y, nargs, i))
		*x = *y+1;
	else
		*x = *x+1;
	
	*y = *x | (1<<(nargs-1-i));

	if (*x>=nlines){
		if (i>0){
			first_pair(x, nargs, i);
			return next_pair_i(pairs, nargs, nlines, i-1);
		}
		else
			return nargs;
	}
	else
		return i;	/* return index of changed pair */
}


bool check_jump(unsigned int n, unsigned int nargs, unsigned int i){
	unsigned int mask = (1<<(nargs-i))-1;

	if((mask & n) == mask)
		return true;
	else
		return false;
}


unsigned int check_equal_output(unsigned int *pairs, unsigned int nargs, unsigned char *output){
	unsigned int i;
	unsigned int x, y;

	for(i=0; i<nargs; i++){
		x = pairs[2*i];
		y = pairs[2*i+1];

		if(output[x]==output[y])
			return i;
	}

	return nargs;
}


unsigned int check_invalid_pairs(unsigned int *pairs, unsigned int nargs, unsigned int nlines, unsigned char *output){
	unsigned int i=0;	/* default points to pair 0, which may mean nothing */
	unsigned int j;

	while( (j = check_equal_output(pairs, nargs, output)) < nargs ){
		/* printf("Equal output.\n"); */
		fflush(stdout);
		i = next_pair_i(pairs, nargs, nlines, j);
	}

	return i;
}


unsigned int count_unique(unsigned int *pairs, unsigned int nargs){
	unsigned int i, j;
	unsigned int nentries = nargs*2;
	unsigned int count = nentries;

	for(i=0; i<nentries; i++){
		for(j=i+2; j<nentries; j++){
			if(pairs[i] == pairs[j]){
				count -= 1;
				break;
			}
		}
	}

	return count;
}


Status check_solution(unsigned int *pairs, unsigned int nargs, unsigned int *saved_pairs, unsigned int *saved_ntests){
	unsigned int ntests;
	unsigned int min_ntests = nargs+1;

	ntests = count_unique(pairs, nargs);

	if(ntests < *saved_ntests){
		*saved_ntests = filter_repeated_pairs(pairs, nargs, saved_pairs);

		bubble_sort(saved_pairs, *saved_ntests);

		if( ntests == min_ntests )
			return End;
		else
			return True;
	}

	return False;
}


unsigned int filter_repeated_pairs(unsigned int *pairs, unsigned int nargs, unsigned int *saved_pairs){
	unsigned int i, j, k;
	bool unique;
	unsigned int nentries = nargs*2;

	k = 0;
	for(i=0; i<nentries; i++){
		unique = true;
		for(j=i+2; j<nentries; j++){
			if(pairs[i] == pairs[j]){
				unique = false;
				break;
			}
		}

		if(unique){
			saved_pairs[k] = pairs[i];
			k++;
		}
	}

	return k;
}
