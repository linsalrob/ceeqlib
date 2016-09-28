

/*
 * ceeq_subsample.h
 *
 * methods for subsampling sequence libraries at random.
 */


#ifndef CEEQ_SUBSAMPLE_H
#define CEEQ_SUBSAMPLE_H


/*
 * subsample_n
 *
 * Randomly choose n char *'s from a list of char *.
 *
 * Parameters:
 *    int      : the number of elements in the array
 *    char *[] : the array of char *'s
 *    int      : the number you want to subsample
 *
 * Returns:
 *    char ** :  a pointer to an array of those IDs.
 *
 */


char **subsample_n(int nseqs, char *arr[], int n);

/* 
 * subsample a fastq file and print the sequences
 *
 * Retrieve nseqs sequences (or all the sequences in the file if nseqs is too small)
 * from fastqfile.
 *
 * Optionally, compressed can be set to true to use a gzipped file
 *
 * Parameters:
 *    int    : the number of sequences to subsample 
 *    char * : the name of the fastq file to subsample
 *    int    : whether the file is compressed. If this value is > 0 then we assume the file
 *             is compressed.
 *
 * Output:
 *    prints the sequences that were subsampled
 *
 * Returns:
 *    int : the number of sequences subsampled. 
 *
 */

int subsample(int, char *, int);

#endif /* CEEQ_SUBSAMPLE_H */
