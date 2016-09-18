
#include <ceeq_fastq.h>
#include <ceeq_subsample.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>

/*
 * A test suite for subsampling fastq files. 
 *
 */

#define ESEQS 5 // the number of sequences we expect to find in the file!
#define SSEQS 2 // the number of sequences we will subsample from this file

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

	// get all the ids from the sequences
	char *ids[nseqs];
	get_ids(ids, seqs);

	// subsample those IDs 
	char **subsample = subsample_n(nseqs, ids, SSEQS);
	
	for (int i=0; i<SSEQS; i++)
		printf("Subsample %d: %s\n", i, subsample[i]);

	/*
	for (int i=0; i<nseqs; i++) {
		char *seq = get_sequence(subsample[i], seqs);
		char *qua = get_quality(subsample[i], seqs);
		printf("%s\n%s\n+\n%s\n", subsample[i], seq, qua);
	}
	return nseqs;
	*/

	if (error)
		fprintf(stderr, "There were %d errors testing the subsampling code\n", error);

	return 0;
}
	








