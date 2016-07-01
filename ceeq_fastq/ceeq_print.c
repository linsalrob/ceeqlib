
#include "ceeq_fastq.h"
#include <stdio.h>
#include <stdlib.h>


/* 
 * print_fastq
 *
 * Print the sequence data structure in fastq format
 * This will not be exactly round robin, because we 
 * do not print the id on the line between the sequences
 * and the quality scores. That is optional and some
 * people do it. But we do not.
 *
 */

void print_fastq(struct fastq *seqs[]) {
	struct fastq *fq;
	for (int i=0; i <= HASHSIZE; i++) {
		fq = seqs[i];
		while (fq != NULL) {
			printf("%s\n%s\n+\n%s\n", fq->info, fq->seq, fq->qual);
			fq = fq->next;
		}
	}
}
		

/*
 * print_fasta
 *
 * Print a fasta version of this data. This does not
 * print the quality scores out.
 *
 */

void print_fasta(struct fastq *seqs[]) {
	struct fastq *fq;
	for (int i=0; i <= HASHSIZE; i++) {
		fq = seqs[i];
		while (fq != NULL) {
			printf(">%s\n%s\n", fq->info, fq->seq);
			fq = fq->next;
		}
	}
}

