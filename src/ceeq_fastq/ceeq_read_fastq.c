/*
 * read_fastq.c
 *
 *
 *  Author: Rob Edwards
 *
 *  Read a fastq file and return a struct containing the sequence and information
 */


#include "ceeq_fastq.h"
#include <ceeq_dupstr.h>
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
	char *ignored; /* this is to suppress a compiler warning*/
	while ((ignored = fgets(line, MAXLINELEN, fp)) != NULL) {

		/* define our fastq data element */
		struct fastq *nfq;
		nfq = (struct fastq *) malloc(sizeof(*nfq));
		if (nfq == NULL) {
			fprintf(stderr, "Can't allocate memory for pointer\n");
			return 0;
		}

		chomp(line);
		/* store the whole line */
		nfq->info = dupstr(line);

		/* store the sequence ID */
		line[strcspn(line, " ")] = '\0';
		nfq->id = dupstr(line);

		/* read the sequence and save it */
		ignored = fgets(line, MAXLINELEN, fp);
		if (line == NULL) {
			fprintf(stderr, "There was no sequence for %s", nfq->info);
			exit(1);
		}

		chomp(line);
		nfq->seq = dupstr(line);

		/* read the next line  and ignore it */
		ignored = fgets(line, MAXLINELEN, fp);

		/* read the quality scores and save them */
		ignored = fgets(line, MAXLINELEN, fp);
		if (line == NULL) {
			fprintf(stderr, "There were no quality scores for %s", nfq->info);
			exit(1);
		}
		chomp(line);
		nfq->qual = dupstr(line);

		if (add(nfq, "id", seqs) != NULL)
			seqcounter++;

	}

	return seqcounter;
}


/* remove the newline from line */
void chomp(char *line) {
	line[strcspn(line, "\r\n")] = '\0';
}

