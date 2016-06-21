/*
 * ceeqlib.h
 *
 *  Created on: Jun 20, 2016
 *      Author: redwards
 */

#ifndef CEEQLIB_H_
#define CEEQLIB_H_

#define VERSION 0.1
#define HASHSIZE 10000
#define VERBOSE 0

/* our fastq data structure.
 *
 * next is a pointer to the next structure
 * seqid is the sequence ID upto the first whitespace
 * seqname is the sequence name including all characters after the first whitespace
 * seq is the sequence
 * qual is the quality scores
 */
struct fastq {
	struct fastq *next;
	char *seqid;
	char *name;
	char *seq;
	char *qual;
};


void read_fastq2(char *, struct fastq *[]);

void help();

void print_fasta(struct fastq *[]);

char **sequence_ids(struct fastq *seqs[], int);
char **sorted_sequence_ids(struct fastq *seqs[], int);

#endif /* CEEQLIB_H_ */
