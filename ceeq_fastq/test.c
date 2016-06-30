
#include <ceeq_fastq.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>

/*
 * A test suite for reading fastq files. This tests all of the methods that we have written 
 *
 */

#define ESEQS 5 // the number of sequences we expect to find in the file!




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

	/* now test the get sequence methods */
	int nnseqs = number_of_sequences(seqs);
	if (nnseqs != ESEQS) {
		printf("There was an error checking the number of sequences. We found %d using number_of_sequences but it should be %d\n", nnseqs, ESEQS);
		error++;
	}

	/* test getting the ids */
	char *ids[nnseqs];
	nnseqs = get_ids(ids, seqs);
	printf("Got %d ids\n", nnseqs);
	for (int i=0; i<nnseqs; i++)
		printf("ID %d: %s\n", i, ids[i]);
	

	char *sq = get_sequence("@GFH7CG303FQFE8/1", seqs);
	char *ans = "AAATACGGGTAGATATACCGCCATGTCTCGCAAACAGCCTCATCATGCCGCGCCTGCCCACTTTTTTGCATCAGTATCCCGGCATTGCGCTGGAACTTTGTAGTAGCGATCGACAGGTCGATTTACTACGGGAAGATTTCGACTGCGTGGTGCGCACAGAGCCGCTACATGCGCCAGGGATACTGACGCGCCCGCTTGGCAAACTGAGAAGAGTGAACTGCGCCAGCCCACAATACCTGGCGCGCTTTGGGTAATCCAGAAAAACCTTGACGATCTCGCCTCACATGCGGTGGTGCATTATTCATTGACCCCGGGAGTTTCTTCACCGGGTTTTGCCTTTGAAACTCCCACGGTATGCAGTGGTAAAAAACCGGCGGAAATGCTAACGGTAAACAGTACGAGACTTGGCATACAGCCTG";
	if (sq == NULL) {
		fprintf(stderr, "Bugger, no sequence for @GFH7CG303FQFE8/1\n");
		error++;
	}

	if (strcmp(sq, ans)) {
		error++;
		printf("The sequence we retrieved for @GFH7CG303FQFE8/1 appeared to be wrong:\n%s\n", sq);
	}

	sq = get_sequence("NOSEQ", seqs);
	if (sq != NULL) {
		fprintf(stderr, "Using ID NOSEQ we retrieved %s\n", sq);
		error++;
	}


	char *qual = get_quality("@GFH7CG303FQFE8/1", seqs);




	
	if (error) 
		fprintf(stderr, "There were %d errors when running the tests\n", error);
	else
		fprintf(stderr, "All tests passed\n");
	
	exit(error);

}
