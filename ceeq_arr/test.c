
#include "ceeq_arr.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr, "Please provide some arguments and we'll shuffle them\n");
		exit(1);
	}
	shuffle(argc-1, argv);
	for (int i=0; i<argc; i++)
		printf("%s\n", argv[i]);
}
