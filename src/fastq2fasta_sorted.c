/*
 * fastq2fasta_sorted.c
 *
 * Author: redwards
 */
#include "ceeqlib.h"
#include "fastq_hash.h"
#include "fastq_read.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		help();
		exit(0);
	}

	struct fastq *seqs[HASHSIZE] = {NULL};
	int nseqs = read_fastq(argv[1], seqs);

	char **ids = sorted_sequence_ids(seqs, nseqs);

	for (int i=0; i<nseqs; i++) {
		int hashval = hash(ids[i]);
		struct fastq *ptr;
		for (ptr=seqs[hashval]; ptr != NULL; ptr = ptr->next)
			if (strcmp(ptr->seqid, ids[i]) == 0)
				printf(">%s\n%s\n", ids[i], ptr->seq);
	}

	/* print_fasta(seqs); */


}


void help() {
	printf("ceeqlib.c\nVersion %f\nCopyright Rob Edwards\n\n", VERSION);
	printf("Usage: fastq2fasta_sorted [fastq file]\n\n");
	printf("    Convert to fasta and print the sequences in sorted (alphanumeric) order\n");
	exit(0);
}
