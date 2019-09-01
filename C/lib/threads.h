#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>

#include "solve.h"

typedef struct {
	unsigned int nargs;
	unsigned int nlines;
	unsigned char *output;
	unsigned int *start;
	unsigned int *saved_pairs;
	unsigned int *saved_ntests;
	bool *end;
	pthread_mutex_t *start_mux;
	pthread_mutex_t *solution_mux;
}ThreadArg;

int solve_with_threads (unsigned int nthreads, unsigned int nargs, unsigned int nlines, unsigned char *output);
int check_valid_nthreads (unsigned int nthreads, unsigned int nargs);
int compare_pairs(unsigned int *pairs1, unsigned int *pairs2, unsigned int npairs);
ThreadArg *to_thread_arg (unsigned int nargs, unsigned int nlines, unsigned char *output, unsigned int *start, unsigned int *saved_pairs, unsigned int *saved_ntests, bool *end, pthread_mutex_t *start_mux, pthread_mutex_t *solution_mux);
void from_thread_arg (ThreadArg *thread_arg, unsigned int *nargs, unsigned int *nlines, unsigned char **output, unsigned int **start, unsigned int **saved_pairs, unsigned int **saved_ntests, bool **end, pthread_mutex_t **start_mux, pthread_mutex_t **solution_mux);
void *find_solution_thread(void *arg);
unsigned int get_start_pairs (unsigned int *pairs, unsigned int *start, unsigned int nargs, unsigned int nlines, pthread_mutex_t *start_mux);
Status check_solution_thread(unsigned int *pairs, unsigned int nargs, unsigned int *saved_pairs, unsigned int *saved_ntests, unsigned char *output, pthread_mutex_t *solution_mux);
void copy_array(unsigned int *from, unsigned int *to, unsigned int n);
bool check_invalid_pairs_thread(unsigned int *pairs, unsigned int nargs, unsigned int nlines, unsigned char *output, unsigned int *i);

#endif /* THREADS_H */
