
#ifndef CEEQ_SUBSAMPLE_H
#define CEEQ_SUBSAMPLE_H

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
char **subsample_n(int nseqs, char *arr[], int n);

/* 
 * subsample a fastq file. 
 *
 * Retriece nseqs sequences (or all the sequences in the file if nseqs is too small)
 * from fastqfile.
 *
 * Optionally, compressed can be set to true to use a gzipped file
 *
 */

int subsample(int, char *, int);

#endif /* CEEQ_SUBSAMPLE_H */
