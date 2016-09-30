

#include "ceeq_arr.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>



/*
 * Fisher-Yates shuffle an array of strings.
 *
 * size is the size of the array, and arr is an array of pointers.
 */
void shuffle(int size, char *arr[]) {
	srand((unsigned int)time(NULL)); // this should not be in the routine. #TODO move it
	for (int i = 0; i<size; i++) {
		int j = size * ((double) rand()/RAND_MAX);
		if (i != j)
			swop(arr, i, j);
	}
}


/*
 * Swop (or swap?) two elements in an array.
 *
 * This is a convenience method for the Fisher Yates shuffle
 */
void swop(char *arr[], int i, int j) {
	char *tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
	if (arr[i] == NULL)
		fprintf(stderr, "Swapping %d and %d resulted in a null for %d\n", i, j, i);
	if (arr[j] == NULL)
		fprintf(stderr, "Swapping %d and %d resulted in a null for %d\n", i, j, j);
}


/*
 * Sum all the numbers in an array at the pointer to this array.
 *
 * Parameters:
 * 	A pointer to the array
 *
 * Returns:
 * 	The sum of numbers in the array
 */

int sum(int nseqs, int *arr) {
	int t=0;
	for (int i=0; i<nseqs; i++) {
		t += *arr;
		arr++;
	}
	return t;
}


/*
 * Compare two ints and return <0, 0, or >0 depending on the relative comparisons.
 *
 * Parameters:
 * 	The two ints to compare
 *
 * Returns:
 * 	An int that is <0 is a is less than b, 0 if they are the same, or >0 if a is bigger than b
 *
 */

int compareints(const void * a, const void * b) {
	return (* (int*) a > * (int *) b) - (* (int *) a < * (int *) b);
}
