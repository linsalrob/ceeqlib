/*
 *
 * ceeq_fastq.h
 *
 * Interface for reading fastq files. We accept compressed or uncompressed files 
 * to read and return a struct that has the fastq data.
 *
 * By default (and currently the only option) we store the sequences in a minimal
 * hash data structure (it is create only, with no option to delete a sequence).
 *
 * We also provide convenience methods to get all the IDs and given and ID to get
 * the sequence and/or quality associated with the read.
 *
 * These code are part of the ceeq_ library and are released as is.
 *
 */

#ifndef CEEQ_FASTQ_H
#define CEEQ_FASTQ_H

#define VERSION 0.2


/* 
 * GENERAL PROTOTYPES AND DEFINITIONS
 *
 */



/*
 * fastq data structure
 * 
 * The struct fastq next is a pointer to the next fastq structure in our collection (hash)
 *
 * This has the fastq data: 
 * 	info is the whole identifier line that we read from the @ sign line
 * 	id is the first word of that line
 * 	seq is the DNA sequence
 * 	qual is the quality score line (this is just the raw string, not the numbers)
 */

struct fastq {
	struct fastq *next;
	char *info;
	char *id;
	char *seq;
	char *qual;
};

#define VERBOSE 1 /* this is a general flag to turn on more output, useful for debugging */


/* 
 * PROTOTYPES AND DEFINITIONS FOR READING THE FASTQ FILE 
 *
 */

/*
 * the maximum line length of the sequence that we'll read
 * I don't have any idea what this should be.
 */

#define MAXLINELEN 10000


int read_fastq(char *filename, struct fastq *seqs[]);
void chomp(char *);





/* 
 * PROTOTYPES AND DEFINITIONS FOR THE HASH DATASTRUCTURE
 *
 */



/* our hashCode should return an integer modded on the table size */
unsigned hash (char *);

struct fastq *lookup(char *, struct fastq *seqs[]);

struct fastq *add(struct fastq *, char [], struct fastq *seqs[]);




#endif /* CEEQ_FASTQ_H */

