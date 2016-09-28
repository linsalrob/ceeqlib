/*
 * ceeq_fastq_pair.h
 *
 * Check paired end files to see if the pairs match.
 *
 * We use a modified version of our fastq data structure specifically for
 * checking paired end files. In this case, we have added a seen flag
 * (essentially a boolean) that lets us know if we have seen this sequence
 * before. We iterate through the first file, and store all the sequences,
 * and then as we stream the second file we note which sequences we find.
 * Sequences in the second file are written directly either to the appropriate
 * pair file or to the singles file. If there is a pair that is also written
 * out. Finally, we iterate through the sequences from the first file, 
 * identifying all those we have not seen and write them out.
 *
 *
 * Author: Rob Edwards
 */

#ifndef CEEQ_FASTQ_PAIR_H_
#define CEEQ_FASTQ_PAIR_H_

#define MAXLINELEN 1000
#define HASHSIZE 10000

/* 
 * This is our modified struct that contains a seen flag. 
 *
 * next is a pointer to the next structure
 * seqid is the sequence ID upto the first whitespace
 * seqname is the sequence name including all characters after the first whitespace
 * seq is the sequence
 * qual is the quality scores
 * seen is a boolean to know if we have printed this sequence
 */
struct fastq_pair_stream {
	struct fastq_pair_stream *next;
	char *seqid;
	char *name;
	char *seq;
	char *qual;
	int seen;
};


/* 
 * The primary method that takes the names of two files and figures out 
 * which sequences in those files are paired, and which sequences are 
 * singletons.
 *
 * Returns the total number of sequences read.
 */

int fastq_pair_stream(char *, char *); /* primary method */

/* 
 * Our hash function to calculate the hash value of a string.
 * Returns an int with that vaue modded on the HASHSIZE
 */
unsigned hash(char *); /* what is the hash value for the string */

/* 
 * Add a sequence to our hash. 
 *
 * This accepts a struct  and adds it to the hash. 
 */
struct fastq_pair_stream *addfqs(struct fastq_pair_stream *s);

#endif /* CEEQ_FASTQ_PAIR_H_ */


