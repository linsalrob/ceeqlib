/*
 * fastq_pair.h
 *
 * Author: redwards
 */

#ifndef FASTQ_PAIR_H_
#define FASTQ_PAIR_H_

/* a structure for our hash of IDs that we have seen */
struct seenids {
	struct seenids *next;
	char *seqid;
};


#endif /* FASTQ_PAIR_H_ */

