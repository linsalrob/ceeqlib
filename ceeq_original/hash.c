
#include "hash.h"

/* calculate the hash for a fastq sequence */
/* we use an unsigned here so that the answer is > 0 */
unsigned hash (char *s) {
	unsigned hashval;

	for (hashval=0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}


