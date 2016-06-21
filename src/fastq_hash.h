/*
 * fastq_hash.h
 *
 *  Created on: Jun 20, 2016
 *      Author: redwards
 */

#ifndef FASTQ_HASH_H_
#define FASTQ_HASH_H_


/* our hashCode should return an integer modded on the table size */
unsigned hash (char *);

struct fastq *lookup(char *, struct fastq *seqs[]);

struct fastq *add(struct fastq *, char [], struct fastq *seqs[]);


#endif /* FASTQ_HASH_H_ */
