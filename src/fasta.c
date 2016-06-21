/*
 * fasta.c
 *
 *      Author: Rob Edwards
 */

#include "ceeqlib.h"
#include <stdio.h>

/* print our fastq structure in fasta format */
void print_fasta(struct fastq *seqs[]) {
	struct fastq *ptr;
	for (int i=0; i<HASHSIZE; i++)
		for (ptr = seqs[i]; ptr != NULL; ptr = ptr->next)
			printf(">%s\n%s\n", ptr->name, ptr->seq);
}
