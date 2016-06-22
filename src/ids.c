/*
 * ids.c
 *
 * Author: Rob Edwards
 */


#include "ceeqlib.h"
#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_strings(const void *, const void *);

/*
 * Extract the IDs from the fastq data structure
 */
char ** sequence_ids(struct fastq *seqs[], int nseqs) {
	char **ids = (char**) malloc(sizeof(char*) * nseqs);
	int j=0;
	struct fastq *ptr;
	for (int i=0; i< HASHSIZE; i++)
		for (ptr = seqs[i]; ptr != NULL; ptr = ptr->next)
			ids[j++] = dupstr(ptr->seqid);
	return ids;
}

/*
 * A comparison function for quicksort. We just using strcmp from string.h
 */
int compare_strings(const void *name1, const void *name2)
{
    const char *name1_ = *(const char **)name1;
    const char *name2_ = *(const char **)name2;
    return strcmp(name1_, name2_);
}

/*
 * Extract a sorted list of sequene IDs from the fastq data structure
 */
char ** sorted_sequence_ids(struct fastq *seqs[], int nseqs) {
	char ** ids = sequence_ids(seqs, nseqs);
	qsort(ids, nseqs, sizeof(char *), compare_strings);
	return ids;
}
