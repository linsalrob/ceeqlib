

/*
 * ceeq_dupstr.h
 *
 * These are straightforward implementations of strdup that duplicates
 * a string, and strcat that concatentates a string. The library
 * implementations are giving a malloc error.
 *
 * Part of the ceeq_ library. These software are released as is.
 *
 */

#ifndef CEEQ_DUPSTR_H_
#define CEEQ_DUPSTR_H_


/* dupstr takes a pointer string and returns a pointer to a copy of that string */
char *dupstr(const char *s);

/* catstr takes two pointers to strings and returns a new pointer to the concatenation of the two strings */
char *catstr(const char *s, const char *t);


#endif /* CEEQ_DUPSTR_H_ */
