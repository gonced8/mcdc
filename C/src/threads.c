#include "threads.h"


int solve_with_threads (unsigned int nthreads, unsigned int nargs, unsigned int nlines, unsigned char *output){
	pthread_t *threads;
	ThreadArg *thread_arg;
	unsigned int *start = (unsigned int *) malloc(2*nargs*sizeof(unsigned int));
	unsigned int *saved_pairs = (unsigned int*) malloc(2*nargs*sizeof(unsigned int));	
	unsigned int saved_ntests = 2*nargs+1;
	unsigned int i;
	bool end = false;

	pthread_mutex_t start_mux;
	pthread_mutex_t solution_mux;

	nthreads = check_valid_nthreads(nthreads, nargs);
	threads = (pthread_t *) malloc(nthreads*sizeof(pthread_t));

	pthread_mutex_init(&start_mux, NULL);
	pthread_mutex_init(&solution_mux, NULL);

	/* Initializing start pairs array */
	for(i=0; i<nargs; i++)
		first_pair(start+2*i, nargs, i);
	
	/* Creating threads */
	for (i=0; i<nthreads; i++){
		thread_arg = to_thread_arg(nargs, nlines, output, start, saved_pairs, &saved_ntests, &end, &start_mux, &solution_mux);
		pthread_create(&(threads[i]), NULL, find_solution_thread, (void *)thread_arg);
	}
	printf("Created %d threads.\n", nthreads);

	for (i=0; i<nthreads; i++){
		pthread_join(threads[i], NULL);
	}
	printf("Exited %d threads.\n", nthreads);

	pthread_mutex_destroy(&start_mux);
	pthread_mutex_destroy(&solution_mux);

	free((unsigned int *) start);
	free((unsigned int *) saved_pairs);

	return 0;
}


int check_valid_nthreads (unsigned int nthreads, unsigned int nargs) {
	unsigned int i;
	unsigned int power = (nargs-1);
	unsigned int ncombinations = 1;
	bool flag = false;

	if (nargs <= 0)
		nthreads = 0;
	else if (nargs <= 1 || nthreads == 0)
		nthreads = 1;
	else{
		for (i=0; i<power; i++) {
			ncombinations = ncombinations << 1;

			if (ncombinations >= nthreads){
				flag = true;
				break;
			}
		}

		if (!flag)
			nthreads = ncombinations;
	}

	return nthreads;
}


int compare_pairs(unsigned int *pairs1, unsigned int *pairs2, unsigned int npairs){
	unsigned int i;
	int comparison = 0;	/* pairs1 are smaller than pairs2 */ 

	for(i=0; i<npairs; i++){
		if ( pairs1[i] < pairs2[i] ){
			comparison = -1;
			break;
		}
		else if ( pairs1[i] == pairs2[i] ){
			continue;
		}
		else if( pairs1[i] > pairs2[i] ){
			comparison = 1;
			break;
		}
	}

	return comparison;
}


ThreadArg *to_thread_arg (unsigned int nargs, unsigned int nlines, unsigned char *output, unsigned int *start, unsigned int *saved_pairs, unsigned int *saved_ntests, bool *end, pthread_mutex_t *start_mux, pthread_mutex_t *solution_mux){
	ThreadArg *thread_arg = (ThreadArg *) malloc(sizeof(ThreadArg));

	thread_arg->nargs = nargs;
	thread_arg->nlines = nlines;
	thread_arg->output = output;
	thread_arg->start = start;
	thread_arg->saved_pairs = saved_pairs;
	thread_arg->saved_ntests = saved_ntests;
	thread_arg->end = end;
	thread_arg->start_mux = start_mux;
	thread_arg->solution_mux = solution_mux;

	return thread_arg;
}


void from_thread_arg (ThreadArg *thread_arg, unsigned int *nargs, unsigned int *nlines, unsigned char **output, unsigned int **start, unsigned int **saved_pairs, unsigned int **saved_ntests, bool **end, pthread_mutex_t **start_mux, pthread_mutex_t **solution_mux){
	*nargs = thread_arg->nargs;
	*nlines = thread_arg->nlines;
	*output = thread_arg->output;
	*start = thread_arg->start;
	*saved_pairs = thread_arg->saved_pairs;
	*saved_ntests = thread_arg->saved_ntests;
	*end = thread_arg->end;
	*start_mux = thread_arg->start_mux;
	*solution_mux = thread_arg->solution_mux;

	free(thread_arg);

	return;
}


void *find_solution_thread(void *arg){
	unsigned int nargs;
	unsigned int nlines;
	unsigned char *output;
	unsigned int *start;
	unsigned int *pairs;
	unsigned int *saved_pairs;
	unsigned int *saved_ntests;
	unsigned int i;
	char res;
	bool *end;
	bool invalid;
	pthread_mutex_t *start_mux;
	pthread_mutex_t *solution_mux;

	from_thread_arg((ThreadArg *)arg, &nargs, &nlines, &output, &start, &saved_pairs, &saved_ntests, &end, &start_mux, &solution_mux);

	pairs = (unsigned int *) malloc(2*nargs*sizeof(nargs));

	while(!(*end)){
		i = get_start_pairs(pairs, start, nargs, nlines, start_mux);
		if(i==nargs){
			*end = true;
		}

		do{
			invalid = check_invalid_pairs_thread(pairs, nargs, nlines, output, &i);
			if(invalid && i<=0 && i>=nargs)
				break;

			/* solution read-write lock and print mutex */
			res = check_solution_thread(pairs, nargs, saved_pairs, saved_ntests, output, solution_mux);

			if(res == End){
				*end = true;
				break;
			}

			i = next_pair(pairs, nargs, nlines);
		}while(!(*end) && i>0 && i<nargs);
	}

	free((unsigned int *) pairs);

	return 0;	


	return NULL;
}


unsigned int get_start_pairs (unsigned int *pairs, unsigned int *start, unsigned int nargs, unsigned int nlines, pthread_mutex_t *start_mux){
	unsigned int i;

	/* lock mutex */
	pthread_mutex_lock(start_mux);

	copy_array(start, pairs, 2*nargs);

	i = next_pair_i(start, nargs, nlines, 0);

	/* unlock mutex */
	pthread_mutex_unlock(start_mux);

	return i;
}


Status check_solution_thread(unsigned int *pairs, unsigned int nargs, unsigned int *saved_pairs, unsigned int *saved_ntests, unsigned char *output, pthread_mutex_t *solution_mux){
	Status code = False;
	unsigned int min_ntests = nargs+1;

	unsigned int ntests = count_unique(pairs, nargs);

	if(ntests < *saved_ntests){
		pthread_mutex_lock(solution_mux);

		if(ntests < *saved_ntests){
			filter_repeated_pairs(pairs, ntests, saved_pairs);
			bubble_sort(saved_pairs, ntests);

			*saved_ntests = ntests;

			print_tests(saved_pairs, *saved_ntests, nargs, output);
			print_pairs(pairs, nargs);
			fflush(stdout);

			if( ntests > min_ntests )
				code = True;
			else
				code = End;
		}

		pthread_mutex_unlock(solution_mux);
	}

	return code;
}


void copy_array(unsigned int *from, unsigned int *to, unsigned int n){
	unsigned int i;

	for(i=0;  i<n; i++){
		to[i] = from[i];
	}
}


bool check_invalid_pairs_thread(unsigned int *pairs, unsigned int nargs, unsigned int nlines, unsigned char *output, unsigned int *i){
	unsigned int j;
	bool invalid = false;

	while( (j = check_equal_output(pairs, nargs, output)) < nargs ){
		/* printf("Equal output.\n");
		fflush(stdout); */
		invalid = true;
		*i = next_pair_i(pairs, nargs, nlines, j);
	}

	return invalid;
}
