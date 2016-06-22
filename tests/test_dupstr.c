/* test my dupstr and catstr methods */

#include "dupstr.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Please provide two strings as arguments\n");
		exit(1);
	}

	char *d = dupstr(argv[1]);
	printf("%s (memory: %p) was duplicated to %s (memory: %p)\n", argv[1], &argv[1], d, &d);

	char *j = catstr(argv[1], argv[2]);
	printf("%s and %s were concatenated to %s (memory: %p)\n", argv[1], argv[2], j, &j);
	return 0;
}

