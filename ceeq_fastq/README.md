#ceeq_fastq

A fastq file is represented by a hash. Each fastq sequence is stored in a struct 
that is part of a linked list:

```
	struct fastq {
		struct fastq *next;
		char *info;
		char *id;
		char *seq;
		char *qual;
	};
```

Each struct has a pointer to the next sequence in the hash. 

Sequences are placed in the hash based on the value calculated by the hash() 
function based on the id of the sequence. The default is to use the id, which 
should be unique, but you can  also opt to use the sequence itself. Using the 
sequence will be slower because the hash function uses the entire string to
calculate the appropriate value.

In addition, the struct contains the info line (which is the full information 
line starting with the @ symbol), the sequence id (which is the first word up
until any whitespace), the sequence, and the quality string.


The functions in [ceeq_fastq.h](ceeq_fastq.h) are all associated with reading 
fastq files and creating this list of fastq objects.

#Functions associated with reading the fastq files.

`int read_fastq(char *filename, struct fastq *seqs[]);`

Read an (uncompressed) fastq file and store the data as a hash in `*seqs[]`. 
This method hashes the sequences based on their ID (which must be unique, 
remember), and returns the number of sequences read from the file.

`int read_fastq_gz(char *filename, struct fastq *seqs[]);`

The analagous function to read_fastq, but this reads from a gzip compressed
file using libz. Also creates the same hash data structure, and returns the
number of sequences read.

`unsigned hash (char *);`

Takes a string and converts it to an int. This function mods that int on the
value of HASHSIZE (defined in ceeq_fastq.h) so that it is ready for use.

`struct fastq *lookup(char *, struct fastq *seqs[]);`

Retrieve a sequence based on its ID.

`struct fastq *add(struct fastq *, char [], struct fastq *seqs[]);`

Add a sequence to the hash. This returns the pointer to the element that
was added to the hash or NULL if the element could not be added to the hash.


#Simple functions that summarize data

`int number_of_sequences(struct fastq *seqs[]);`

Returns the number of sequences in the hash

`char *get_sequence(char *id, struct fastq *seqs[]);`

Return the DNA sequence for a given ID

`char *get_quality(char *id, struct fastq *seqs[]);`

Return the quality scores for a given ID

`int get_ids(char *ids[], struct fastq *seqs[]);`

Get an array of the ids for all of the sequences.



#Functions for printing the sequences

`void print_fastq(struct fastq *seqs[]);`

print the sequences and their quality scores in fastq format.

`void print_fasta(struct fastq *seqs[]);`

print the sequences (only) in fasta format.






