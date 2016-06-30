
#include <string.h>

/* 
 * These are just a few accesory functions for manipulating lines
 * that we need from time to time
 */



/* remove the newline from line */
void chomp(char *line) {
	line[strcspn(line, "\r\n")] = '\0';
}

/* remove the first character from the character array */
void pop(char *line) {
	int i;
	for (i=1; line[i] != '\0'; i++)
		line[i-1]=line[i];
	line[i]='\0';
}


