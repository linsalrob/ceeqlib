

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


void swop(char *arr[], int i, int j) {
	char *tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
	if (arr[i] == NULL)
		fprintf(stderr, "Swapping %d and %d resulted in a null for %d\n", i, j, i);
	if (arr[j] == NULL)
		fprintf(stderr, "Swapping %d and %d resulted in a null for %d\n", i, j, j);
}

