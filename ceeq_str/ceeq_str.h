

/*
 * ceeq_str.h
 *
 * These are straightforward implementations of str functions.
 * Some of the standard library implementations are giving a 
 * malloc error.
 *
 * Part of the ceeq_ library. These software are released as is.
 *
 */

#ifndef CEEQ_STR_H_
#define CEEQ_STR_H_


/* 
 * Duplicate a string.
 *
 * dupstr takes a pointer string and returns a pointer to a copy of that string
 */
char *dupstr(const char *s);

/*
 * Concatenate two strings
 *
 * catstr takes two pointers to strings and returns a new pointer to the concatenation of the two strings 
 */
char *catstr(const char *s, const char *t);

/* 
 * Remove a new line from the the end of a string
 * 
 * chomp (named after the PERL function) takes a string and removes the new line from the end
 */
char *chomp(char *);

/*
 * Remove the first character from a string
 *
 * remove the first character from a pointer to a string
 */
char *pop(char *);

/*
 * get the substring of the first word (ie. upto the first white space character) if there is one in the string 
 */
char *firstword(char *line);

#endif /* CEEQ_STR_H_ */
