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

/* 
 * read a fastq file from an uncompressed file
 *
 * This takes a file name and an array of structs that we'll use
 * to create a hash of the sequences based on their IDs. 
 *
 * Note that we consider the ID to be from the @ to the first whitespace
 * in the information line. We include the @ in the ID (to make things
 * faster).
 *
 * We return the number of sequences read
 */
int read_fastq(char *filename, struct fastq *seqs[]);

/*
 * read a fastq file from a gzip compressed file
 * this is analogous to the above method, and returns the same
 * hashed data structure, but it reads a gzip compressed file.
 */
int read_fastq_gz(char *filename, struct fastq *seqs[]);


/* 
 * PROTOTYPES AND DEFINITIONS FOR THE HASH DATASTRUCTURE
 *
 */

#define HASHSIZE 10000

/* hash returns an integer already modded on the table size */
unsigned hash (char *);

/* 
 * Look up an entry based on its hash function.
 * If it is there we return a pointer otherwise we return NULL
 */

struct fastq *lookup(char *, struct fastq *seqs[]);

/* 
 * Add a sequence to the hash.
 *
 * The first argument is our fastq structure
 * The second argument is one of "info" (for the whole id line), "seq" or "sequence" (to hash by the sequence), 
 * "id" to hash by the first word on the id line. The default is to use "id".
 *
 * The third argument is a pointer to an array of structs that is our hash
 *
 */
struct fastq *add(struct fastq *, char [], struct fastq *seqs[]);



/* 
 * PROTOTYPES AND DEFINITIONS FOR THE GET SEQUENCES FUNCTIONS
 *
 */

/* return the number of sequences in the hash */
int number_of_sequences(struct fastq *seqs[]);

/* return the DNA sequence for a given ID */
char *get_sequence(char *id, struct fastq *seqs[]);

/* return the quality scores for a given ID */
char *get_quality(char *id, struct fastq *seqs[]);

/* get an array of the ids */
int get_ids(char *ids[], struct fastq *seqs[]);


// PROTOTYPES FOR PRINTING THE SEQUENCES

/* 
 * print_fastq
 *
 * Print the sequence data structure in fastq format
 * This will not be exactly round robin, because we 
 * do not print the id on the line between the sequences
 * and the quality scores. That is optional and some
 * people do it. But we do not.
 *
 */

void print_fastq(struct fastq *seqs[]);


/*
 * print_fasta
 *
 * Print a fasta version of this data. This does not
 * print the quality scores out.
 *
 */

void print_fasta(struct fastq *seqs[]);

#endif /* CEEQ_FASTQ_H */

