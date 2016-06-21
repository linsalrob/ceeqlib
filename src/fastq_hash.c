/*
 * fastq.c
 *
 *  Created on: Jun 19, 2016
 *      Author: redwards
 */

#include "ceeqlib.h"
#include "fastq_hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




/* calculate the hash for a fastq sequence */
/* we use an unsigned here so that the answer is > 0 */
unsigned hash (char *s) {
	unsigned hashval;

	for (hashval=0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;


}


/* look up an entry based on its hash function.
 * If it is there we return a pointer otherwise we return NULL
 */

struct fastq *lookup(char *s, struct fastq *seqs[]) {
	struct fastq *ptr;

	ptr = seqs[hash(s)];

	for (ptr = seqs[hash(s)]; ptr != NULL; ptr = ptr->next) {
		if (strcmp(s, ptr->seq) == 0)
			return ptr;
	}

	return NULL;
}

/* add a sequence to the hash.
 *
 * struct fastq *s is our fastq structure
 * hashby is one of "name", "seq" or "sequence", "id" or "seqid" to choose the key for the hash. Default is seqid
 * seqs is a pointer to an array of structs that is our hash
 */

struct fastq *add(struct fastq *s, char hashby[], struct fastq *seqs[]) {
	struct fastq *ptr;
	unsigned hashval;

	char *key;
	if (strcmp(hashby, "name") == 0)
			key = s->name;
	else if (strcmp(hashby, "seq") == 0 || strcmp(hashby, "sequence") == 0)
			key = s->seq;
	else
		key = s->seqid;

	if ((ptr = lookup(key, seqs)) == NULL) {
		/* we don't have this element */
		ptr = (struct fastq *) malloc(sizeof(*ptr));
		if (ptr == NULL) {
			fprintf(stderr, "Can't allocate memory for pointer\n");
			return NULL;
		}

		if (((ptr->seqid = strdup(s->seqid)) == NULL) ||
				((ptr->seq = strdup(s->seq)) == NULL) ||
				((ptr->name = strdup(s->name)) == NULL) ||
				((ptr->qual = strdup(s->qual)) == NULL)) {
			fprintf(stderr, "Can't duplicate struct\n");
			return NULL;
		}

		/* this is an add first */
		hashval = hash(key);
		ptr->next = seqs[hashval];
		seqs[hashval] = ptr;
	}
	else {
		if (VERBOSE > 0)
			fprintf(stderr, "Key %s is already present in the hash\n", key);
		return NULL;
	}

	return ptr;
}
