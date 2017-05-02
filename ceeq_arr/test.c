
#include "ceeq_arr.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr, "Please provide some arguments and we'll shuffle them\n");
		exit(1);
	}
	shuffle(argc, argv);
	for (int i=0; i<argc; i++)
		printf("%s\n", argv[i]);

	// create an array of 5 numbers
	int arr[5] = {2, 4, 6, 8, 10};
	int s = sum(5, arr);
	if (s != 30) 
		printf("The array should sum to 30 but sums to %d\n", s);

	int a = 3;
	for (int b = 1; b < 6; b++) {
		printf("Comparing %d to %d resulted in %d\n", a, b, compareints(&a, &b));
	}
}
