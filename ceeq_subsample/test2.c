

#include <ceeq_str.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char **cp = (char **)  malloc(sizeof(char*) * argc  + 1);
	for (int i=0; i<argc; i++) {
		printf("Copying %s\n", argv[i]);
		cp[i] = dupstr(argv[i]);
	}

	printf("Printing\n");
	for (int i=0; i<argc; i++)
		printf("Found %s\n", cp[i]);
}

