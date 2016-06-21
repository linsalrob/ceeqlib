/*
 * fastq_read.h
 *
 * Author: Rob Edwards
 */

#ifndef FASTQ_READ_H_
#define FASTQ_READ_H_

#define MAXLINELEN 1000 /* this would be a long sequence for a fastq file! */

int read_fastq(char *filename, struct fastq *seqs[]);
void chomp(char *);



#endif /* FASTQ_READ_H_ */
