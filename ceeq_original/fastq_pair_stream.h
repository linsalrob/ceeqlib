/*
 * fastq_pair_stream.h
 *
 * Author: Rob Edwards
 */

#ifndef FASTQ_STREAM_H_
#define FASTQ_STREAM_H_

#define MAXLINELEN 1000

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

int fastq_pair_stream(char *, char *); /* primary method */

unsigned hash(char *); /* what is the hash value for the string */
struct fastq_pair_stream *addfqs(struct fastq_pair_stream *s);

#endif /* FASTQ_STREAM_H_ */


