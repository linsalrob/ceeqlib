
#include "ceeq_str.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* 
 * These are just a few accesory functions for manipulating lines
 * that we need from time to time
 */



/* remove the newline from line */
char *chomp(char *line) {
	int idx = strcspn(line, "\r\n");
	char *newline = malloc(sizeof(char) * idx + 1);
	strncpy(newline, line, idx);
	return newline;
}

/* remove the first character from the character array */
char *pop(char *line) {
	line++;
	return line;
}


/* get the substring upto the first white space character if there is one in the string */
char *firstword(char *line) {
	int idx = strcspn(line, " \n\r\t");
	char *newline = malloc(sizeof(char) * idx + 1);
	if (newline == NULL) {
		fprintf(stderr, "Couldn't allocate memory for newline\n");
		exit(1);
	}
	strncpy(newline, line, idx);
	return newline;
}


