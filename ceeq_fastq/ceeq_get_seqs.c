
#include "ceeq_fastq.h"
#include <stdlib.h>
#include <string.h>

/*
 * methods to get the sequence(s) and their IDs from our data structure.
 *
 * These are the methods you should use after you have read the fastq file
 */


/*
 * Return the number of sequences in the hash. This is straightforward, but a good place to start!
 */
int number_of_sequences(struct fastq *seqs[]) {
	int n = 0;
	struct fastq *fq;
	for (int i=0; i<=HASHSIZE; i++) {
		fq = seqs[i];
		while ((fq != NULL) && n++ && (fq = fq->next))
			;
	}

	return n;
}


/*
 * Get a sequence from its ID.
 * id is the string for an ID. 
 * seqs is the hash
 * returns the DNA sequence, or NULL if the sequence was not found
 */
char *get_sequence(char *id, struct fastq *seqs[]) {
	struct fastq *fq = seqs[hash(id)];
	if (fq == NULL)
		return NULL;
	while ((fq != NULL) && strcmp(fq->id, id) && (fq = fq->next))
		;
	return fq->seq;
}

/*
 * Get a quality scores for a sequence from its ID.
 * id is the string for an ID. 
 * seqs is the hash
 * returns the quality scores or NULL if the sequence was not found
 */
char *get_quality(char *id, struct fastq *seqs[]) {
	struct fastq *fq = seqs[hash(id)];
	if (fq == NULL)
		return NULL;
	while ((fq != NULL) && strcmp(fq->id, id) && (fq = fq->next))
		;
	return fq->qual;
}


/*
 * Get a list of all the ids. We need a pointer to an array to put the ids
 * and the pointer to the hash of data.
 *
 * Populates the array and returns the number of IDs found
 *
 */

int get_ids(char *ids[], struct fastq *seqs[]) {
	struct fastq *fq;
	int j = 0;
	for (int i=0; i<HASHSIZE; i++) {
		fq = seqs[i];
		while ((fq != NULL) && (ids[j++] = fq->id) && (fq = fq->next))
			;
	}

	return j;
}
