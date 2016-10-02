
#include <ceeq_fastq.h>
#include <ceeq_arr.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>

/*
 * A test for counting things from fastq files. 
 * This tests eg. lengths and numbers
 *
 */


#define ESEQS 5 // the number of sequences we expect to find in the file!
#define TESTPRINT 1 // this is a boolean that determines whether we test printing fastq and fasta sequences. You can leave this set to 0 

int main(int argc, char *argv[]) {
	// this file has 5 sequences in it so it should be easy to read!
	char *filename = "../example_data/small.fastq";
	struct fastq *seqs[HASHSIZE] = {NULL};
	int nseqs = read_fastq(filename, seqs);
	int error = 0;
	if (nseqs != ESEQS) {
		fprintf(stderr, "There was an error reading %s. We retrieved %d sequences but should have found %d sequences\n", filename, nseqs, ESEQS);
		error = 1;
	}

	// create an array of integers and count the lengths of these 
	// sequences
	int lens[nseqs];
	int lseqn = sequence_lengths(seqs, lens);
	if (TESTPRINT) {
		printf("Test counted the lengths of %d sequences: ", lseqn);
		for (int i =0; i<nseqs; i++)
			printf("%d ", lens[i]);
	}
	printf("\n");

	
	// create an array of integers and get the sorted lengths of
	// sequences
	int slens[nseqs];
	int slseqn = sorted_sequence_lengths(seqs, slens);
	if (TESTPRINT) {
		printf("Retrieved sorted lengths of %d sequences: ", slseqn);
		for (int i =0; i<nseqs; i++)
			printf("%d ", slens[i]);
	}
	printf("\n");

	



	if (error)
		printf("There were %d errors\n", error);
}


