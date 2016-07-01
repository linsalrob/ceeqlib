/*
 * Test str library to make sure works as expected!
 */

#include <ceeq_str.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char *s1 = "string one";
	char *s2 = "string two";

	char *dup = dupstr(s1);

	printf("'%s' with address %p was duplicated to '%s' with address %p\n", s1, &s1, dup, &dup);
	
	char *sc = catstr(s1, s2);
	printf("'%s' and '%s' were concatenated to '%s'\n", s1, s2, sc);

	char *s3 = "string three\n";
	printf("This string with a new line: %s\n", s3);
	s3 = chomp(s3);
	printf("Was chomped to remove the new line: %s\n", s3);
	
	s3 = pop(s3);
	printf("And now there is no s: %s\n", s3);

	printf("For string '%s'\n", s1);
	char *fw = firstword(s1);
	printf("The first word is '%s'\n", fw);
}


