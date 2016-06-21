/*
 ============================================================================
 Name        : ceeqlib.c
 Author      : Rob Edwards
 Version     :
 Copyright   : This work is released under the MIT License
 Description : The ceeqlib (pronounced seq lib) is a C library for
             : manipulating DNA sequences
 ============================================================================
 */

#include "ceeqlib.h"
#include "fastq_read.h"
#include "fastq_hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char *argv[]) {
	if (argc < 3) {
		help();
		exit(0);
	}

	if (strcmp(argv[1], "fastq2fasta") == 0) {
		struct fastq *seqs[HASHSIZE] = {NULL};
		read_fastq(argv[2], seqs);
		print_fasta(seqs);
		exit(0);
	}
	if (strcmp(argv[1], "fastq2fasta_sorted") == 0) {
		struct fastq *seqs[HASHSIZE] = {NULL};
		int nseqs = read_fastq(argv[2], seqs);
		fprintf(stderr, "Read %d sequences\n", nseqs);
		char **ids = sorted_sequence_ids(seqs, nseqs);

		for (int i=0; i<nseqs; i++) {
			int hashval = hash(ids[i]);
			struct fastq *ptr;
			for (ptr=seqs[hashval]; ptr != NULL; ptr = ptr->next)
				if (strcmp(ptr->seqid, ids[i]) == 0)
					printf(">%s\n%s\n", ids[i], ptr->seq);
		}
	}
	else {
		help();
	}

}


void help() {
	printf("ceeqlib.c\nVersion %f\nCopyright Rob Edwards\rReleased under the MIT license\n\n", VERSION);
	printf("Usage: ceeqlib [command] [file1] [file2]\n\n");
	printf("    fastq2fasta [fastq file]           print the fastq file in fasta format\n");
	printf("    fastq2fasta_sorted [fastq file]    print the fastq file with the sequence ids sorted\n");
	exit(0);
}
