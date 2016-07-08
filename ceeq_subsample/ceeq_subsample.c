

#include "ceeq_subsample.h"
#include <ceeq_fastq.h>
#include <ceeq_str.h>
#include <ceeq_arr.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


/*
 * Routines for subsampling from a fastq library.
 */


/*
 * subsample_n
 *
 * Randomly choose n char *'s from a list of char *.
 * The parameters are the total number of things in the list,
 * the list, and the number that we want to choose.
 *
 * Returns a pointer to an array of those IDs.
 *
 */

char **subsample_n(int nseqs, char *arr[], int n) {
	shuffle(nseqs, arr);
	char **newarr = (char **) malloc(sizeof(char*) * n + 1);
	for (int i=0; i<n; i++)
		newarr[i] = dupstr(arr[i]);
	
	return newarr;
}




