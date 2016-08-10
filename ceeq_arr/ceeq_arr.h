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
 * Fisher-Yates shuffle an array of strings.
 *
 * size is the size of the array, and arr is an array of pointers.
 */
void shuffle(int size, char *arr[]);

/*
 * Swop two elements in an array. Given an array of pointers and 
 * two locations we swap the two elements. This is a conveniene method!
 */

void swop(char *arr[], int, int);


#endif /* CEEQ_ARR_H_ */


