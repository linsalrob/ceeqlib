/*
 * strdup() is not part of POSIX and is causing crashes on my CentOS systems.
 *
 * This is a simple implementation of strdup() but we can't call it that!
 * 
 * For more information see http://stackoverflow.com/questions/8359966/strdup-returning-address-out-of-bounds
 */

#include "ceeq_dupstr.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *dupstr(const char *s) {
	char *const result = malloc(strlen(s) + 1);
	if (result == NULL) {
		fprintf(stderr, "Cannot allocate memory to duplicate %s\n", s);
		exit(1);
	}
	strcpy(result, s);
	return result;
}

char *catstr(const char *s, const char *t) {
	char *const result = malloc(strlen(s) + strlen(t) + 1);
	if (result == NULL) {
		fprintf(stderr, "Cannot allocate memory for catstr of %s and %s\n", s, t);
		exit(1);
	}
	int i;
	for (i=0; i<strlen(s); i++) 
		result[i] = s[i];
	for (int j=0; j<strlen(t); j++)
		result[i++] = t[j];
	result[i]='\0';
	return result;
}
