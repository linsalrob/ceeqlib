
#include "ceeq_str.h"
#include <string.h>
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


