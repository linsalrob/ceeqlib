

/*
 * ceeq_str.h
 *
 * These are straightforward implementations of strdup that duplicates
 * a string, and strcat that concatentates a string. The library
 * implementations are giving a malloc error.
 *
 * Part of the ceeq_ library. These software are released as is.
 *
 */

#ifndef CEEQ_STR_H_
#define CEEQ_STR_H_


/* dupstr takes a pointer string and returns a pointer to a copy of that string */
char *dupstr(const char *s);

/* catstr takes two pointers to strings and returns a new pointer to the concatenation of the two strings */
char *catstr(const char *s, const char *t);

/* remove the new line from a line read from a file */
char *chomp(char *);

/* remove the first character from a pointer to a line */
char *pop(char *);

/* get the substring of the first word (ie. upto the first white space character) if there is one in the string */
char *firstword(char *line);

#endif /* CEEQ_STR_H_ */
