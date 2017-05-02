

/*
 * dupstr.h
 *
 * Author: Rob Edwards
 */

#ifndef DUPSTR_H_
#define DUPSTR_H_


/* this is a drop in replacement for strdup() */
char *dupstr(const char *s);
char *catstr(const char *s, const char *t);


#endif /* DUPSTR_H_ */
