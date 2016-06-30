/*
 * Test dupstr library to make sure works as expected!
 */

#include <ceeq_dupstr.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	char *s1 = "string one";
	char *s2 = "string two";

	char *dup = dupstr(s1);

	printf("'%s' with address %p was duplicated to '%s' with address %p\n", s1, &s1, dup, &dup);
	
	char *sc = catstr(s1, s2);
	printf("'%s' and '%s' were concatenated to '%s'\n", s1, s2, sc);
}


