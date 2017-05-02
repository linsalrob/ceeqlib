

#include "ceeq_subsample.h"
#include <ceeq_fastq.h>
#include <ceeq_str.h>
#include <ceeq_arr.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


/*
 * Routines for subsampling from a fastq library.
 */


/*
 * subsample_n
 *
 * Randomly choose n char *'s from a list of char *.
 * The parameters are the total number of things in the list,
 * the list, and the number that we want to choose.
 *
 * Returns a pointer to an array of those IDs.
 *
 */

char **subsample_n(int nseqs, char *arr[], int n) {
	shuffle(nseqs, arr);
	char **newarr = (char **) malloc(sizeof(char*) * n + 1);
	for (int i=0; i<n; i++)
		newarr[i] = dupstr(arr[i]);
	
	return newarr;
}

/* 
 * subsample a fastq file and print sequences in fastq format
 *
 * Retrieve nseqs sequences (or all the sequences in the file if nseqs is too small)
 * from fastqfile.
 *
 * Optionally, compressed can be set to true to use a gzipped file
 *
 */

int subsample_print(int nseqs, char *fastqfile, int compressed) {

	// read the fastq file into our hash called seqs
	
	struct fastq *seqs[HASHSIZE] = {NULL};

	int read_seqs = 0;
	if (compressed)
		read_seqs = read_fastq_gz(fastqfile, seqs);
	else
		read_seqs = read_fastq(fastqfile, seqs);

	if (read_seqs < nseqs) {
		fprintf(stderr, "You requested %d sequences but there are only %d in the file!\n", nseqs, read_seqs);
		nseqs = read_seqs;
	}

	// get all the ids from the sequences
	char *ids[read_seqs];
	get_ids(ids, seqs);

	// subsample those IDs 
	char **subsample = subsample_n(read_seqs, ids, nseqs);

	for (int i=0; i<nseqs; i++) {
		char *seq = get_sequence(subsample[i], seqs);
		char *qua = get_quality(subsample[i], seqs);
		printf("%s\n%s\n+\n%s\n", subsample[i], seq, qua);
	}
	return nseqs;
}


/* 
 * subsample a fastq file. 
 *
 * Retrieve nseqs sequences (or all the sequences in the file if nseqs is too small)
 * from fastqfile and store them in the hash provided as seqs (this should be a 
 * struct fastq *seqs[HASHSIZE] array).
 *
 * Optionally, compressed can be set to true to use a gzipped file
 *
 * Returns the number of sequences that were added to the hash.
 *
 */

int subsample(int nseqs, char *fastqfile, struct fastq *seqs[], int compressed) {


	// read the fastq file into a temporary hash
	struct fastq *allseqs[HASHSIZE] = {NULL};

	int read_seqs = 0;
	if (compressed)
		read_seqs = read_fastq_gz(fastqfile, allseqs);
	else
		read_seqs = read_fastq(fastqfile, allseqs);

	if (read_seqs < nseqs) {
		fprintf(stderr, "You requested %d sequences but there are only %d in the file!\n", nseqs, read_seqs);
		nseqs = read_seqs;
	}

	// get all the ids from the sequences
	char *ids[read_seqs];
	get_ids(ids, allseqs);

	// subsample those IDs 
	char **subsample = subsample_n(read_seqs, ids, nseqs);

	for (int i=0; i<nseqs; i++) {
		char *info = get_seq_information(subsample[i], seqs);
		char *seq = get_sequence(subsample[i], seqs);
		char *qua = get_quality(subsample[i], seqs);
	
	}
	return nseqs;
}



