/*
 * read_fastq.c
 *
 *
 *  Author: Rob Edwards
 *
 *  Read a fastq file and return a hash of the sequences.
 */


#include "ceeqlib.h"
#include "fastq_read.h"
#include "fastq_hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* read_fastq
 *
 * Read a fastq file and return the number of sequences read.
 *
 * Requires a pointer to a string for the file name, and a
 * pointer to the hash where we should store the data.
 *
 */

int read_fastq(char *filename, struct fastq *seqs[]) {

	FILE *fp;

	char line[MAXLINELEN];
	int seqcounter=0;

	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "Can't open file %s\n", filename);
		exit(1);
	}

	/* at the moment I'm using fgets, but I should probably change this to getline() */
	while ((fgets(line, MAXLINELEN, fp)) != NULL) {

		/* define our fastq data element */
		struct fastq *nfq;
		nfq = (struct fastq *) malloc(sizeof(*nfq));
		if (nfq == NULL) {
			fprintf(stderr, "Can't allocate memory for pointer\n");
			return 0;
		}

		chomp(line);
		/* store the whole line */
		nfq->name = strdup(line);

		/* store the sequence ID */
		line[strcspn(line, " ")] = '\0';
		nfq->seqid = strdup(line);

		/* read the sequence and save it */
		fgets(line, MAXLINELEN, fp);
		if (line == NULL) {
			fprintf(stderr, "There was no sequence for %s", nfq->name);
			exit(1);
		}
		chomp(line);
		nfq->seq = strdup(line);

		/* read the next line  and ignore it */
		fgets(line, MAXLINELEN, fp);

		/* read the quality scores and save them */
		fgets(line, MAXLINELEN, fp);
		if (line == NULL) {
			fprintf(stderr, "There were no quality scores for %s", nfq->name);
			exit(1);
		}
		chomp(line);
		nfq->qual = strdup(line);

		if (add(nfq, "id", seqs) != NULL)
			seqcounter++;

	}

	return seqcounter;
}


/* remove the newline from line */
void chomp(char *line) {
	line[strcspn(line, "\r\n")] = '\0';
}

