/*
 * ceeq_arr.h
 *
 * These are methods for manipulating lists. We take pointers to arrays
 * and do things with them.
 *
 * Part of the ceeq_ library. These software are released as is.
 *
 */

#ifndef CEEQ_ARR_H_
#define CEEQ_ARR_H_

/*
 * Shuffle an array of strings. The default implementation uses the Fisher-Yates shuffle.
 *
 * size is the size of the array, and arr is an array of pointers.
 */
void shuffle(int size, char *arr[]);

/*
 * Swop two elements in an array. Given an array of pointers and 
 * two locations we swap the two elements. This is a convenience method for the shuffle algorithm!
 */

void swop(char *arr[], int, int);


/*
 * Sum all the numbers in an array at the pointer to this array.
 *
 * Parameters:
 * 	A pointer to the array
 *
 * Returns:
 * 	The sum of numbers in the array
 */

int sum(int nseqs, int *arr);


#endif /* CEEQ_ARR_H_ */


