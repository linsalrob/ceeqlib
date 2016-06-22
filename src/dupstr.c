/*
 * strdup() is not part of POSIX and is causing crashes on my CentOS systems.
 *
 * This is a simple implementation of strdup() but we can't call it that!
 * 
 * For more information see http://stackoverflow.com/questions/8359966/strdup-returning-address-out-of-bounds
 */

#include <stdlib.h>
#include <string.h>

char *dupstr(const char *s) {
	char *const result = malloc(strlen(s) + 1);
	if (result != NULL) {
		strcpy(result, s);
	}
	return result;
}
