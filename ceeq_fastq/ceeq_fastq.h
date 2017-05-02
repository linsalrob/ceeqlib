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
 * The struct fastq next is a pointer to the next fastq structure in our collection. These
 * structs are stored in array based on the value returned from hash using (usually) the 
 * sequence.
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
 * I don't have any idea what this should be, so I set it to
 * 10,000
 *
 */

#define MAXLINELEN 10000

/* 
 * read a fastq file from an uncompressed file
 *
 * Parameters:
 * This method takes a file name and an array of structs that we'll use
 * to create a hash of the sequences based on their IDs. 
 *
 * Note that we consider the ID to be from the @ to the first whitespace
 * in the information line. We include the @ in the ID (to make things
 * faster).
 *
 * Returns:
 * Returns the number of sequences read from the file
 */
int read_fastq(char *filename, struct fastq *seqs[]);

/*
 * read a fastq file from a gzip compressed file
 * this is analogous to the above method, and creates the same
 * hashed data structure, but it reads a gzip compressed file.
 *
 * Returns:
 * Returns the number of sequences read from the file
 */
int read_fastq_gz(char *filename, struct fastq *seqs[]);


/* 
 * PROTOTYPES AND DEFINITIONS FOR THE HASH DATASTRUCTURE
 *
 */

#define HASHSIZE 10000

/* 
 * The hash function takes a string and converts it to an int.
 *
 * Parameters:
 * a string
 *
 * Returns:
 * Returns an integer already modded on the value of HASHSIZE
 */
unsigned hash (char *);

/* 
 * Look up an entry in the hash based on its hash function.
 * 
 * Remember the default is to hash sequences by their ID, so
 * if you pass in an ID you will get the a pointer to the
 * struct that represents that sequence (including the sequence 
 * and the quality scores).
 *
 * Returns:
 * If it is there we return a pointer otherwise we return NULL
 */

struct fastq *lookup(char *, struct fastq *seqs[]);

/* 
 * Add a sequence to the hash.
 *
 * Parameters:
 * The first argument is our fastq structure that we are going to add
 *
 * The second argument is one of "info" (for the whole id line), 
 * "seq" or "sequence" (to hash by the sequence), or "id" to hash by 
 * the first word on the id line. The default is to use "id" to hash
 * the sequences. Note the comment above about the length of the id
 * versus the sequences.
 *
 * The third argument is a pointer to an array of structs that contains
 * our hash and to which the sequences will be added.
 *
 * Returns:
 * Returns the element that was added to the hash, or NULL if we 
 * are not able to add the element to the hash for some reason (e.g.
 * the sequence is already there).
 *
 */
struct fastq *add(struct fastq *, char [], struct fastq *seqs[]);



/* 
 * PROTOTYPES AND DEFINITIONS FOR THE GET SEQUENCES FUNCTIONS
 *
 */

/* 
 * Return the number of sequences in the hash.
 *
 * Parameters:
 * seqs[] is the hash containing the sequences
 *
 * Returns:
 * returns the number of sequences
 */
int number_of_sequences(struct fastq *seqs[]);

/* 
 * Return the DNA sequence for a given ID 
 *
 * Parameters:
 * *id is the ID of the sequence you would like to get
 * seqs[] is the hash containing the sequences
 *
 * Returns:
 * returns a pointer to the DNA sequence
 */
char *get_sequence(char *id, struct fastq *seqs[]);

/* 
 * Return the quality scores for a given ID 
 *
 * Parameters:
 * *id is the ID of the sequence you would like to get
 * seqs[] is the hash containing the sequences
 *
 * Returns:
 * returns the string representation of the quality scores
 */
char *get_quality(char *id, struct fastq *seqs[]);

/*
 * Get the full identifier for a sequence from its ID.
 *
 * Parameters:
 * id is the string for an ID
 * seqs is hte hash
 *
 * Returns:
 * returns the full identifier or NULL if the sequence was not found
 */

char *get_seq_information(char *id, struct fastq *seqs[]);

/* 
 * Create an array of all the sequence ids
 *
 * ids[] is the array that will be populated with the ids
 * seqs[] is the hash containing the sequences
 * returns the number of ids that were found and added to the array
 */
int get_ids(char *ids[], struct fastq *seqs[]);


/*
 * Create an array of the lengths of the sequences.
 *
 * This is a convenience method that then allows you to calculate
 * eg. N50, mean, median, etc lengths
 *
 * Parameters:
 * num_seqs is the number of sequences in the hash
 * seqs[] is the hash containing the sequences
 *
 * Returns:
 * int [] of the lengths of all the sequences
 */

int sequence_lengths(struct fastq *seqs[], int []);

/*
 * Get the sequence lengths sorted from lowest to highest.
 *
 * This uses sequence lengths, and then calls quick sort to sort them.
 *
 * Parameters:
 *   hash of sequences
 *   array to store the lengths of the sequences (should be the appropriate size)
 *
 * Returns:
 *   Returns the number of sequences that were read.
 */

int sorted_sequence_lengths(struct fastq *seqs[], int lens[]);


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




