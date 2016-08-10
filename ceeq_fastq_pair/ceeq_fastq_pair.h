/*
 * fastq_pair_stream.h
 *
 * Author: Rob Edwards
 */

#ifndef CEEQ_FASTQ_PAIR_H_
#define CEEQ_FASTQ_PAIR_H_

#define MAXLINELEN 1000
#define HASHSIZE 10000

/* our fastq data structure.
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


/* the primary method that takes two file names and figures out what sequences
 * are pairs
 */

int fastq_pair_stream(char *, char *); /* primary method */

/* calculate the hash value of a string */
unsigned hash(char *); /* what is the hash value for the string */

/* add a fastqpair stream to our hash */
struct fastq_pair_stream *addfqs(struct fastq_pair_stream *s);

#endif /* CEEQ_FASTQ_PAIR_H_ */


