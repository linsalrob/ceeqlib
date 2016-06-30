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
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* read_fastq
 *
 * Read a fastq file and return the number of sequences read.
 *
 * By default we include the @ in the sequence identifier. 
 * This is a O(n) operation to remove (where n=length of id)
 * and so it is costly to do for every sequence. There is a pop
 * method here that you can use to remove that sign if you don't
 * want it.
 *
 * Requires a pointer to a string for the file name, and a
 * pointer to the hash where we should store the data.
 *
 */

int read_fastq_gz(char *filename, struct fastq *seqs[]) {

	gzFile fp;

	char *line = malloc(sizeof(char) * MAXLINELEN + 1);
	int seqcounter=0;

	if ((fp = gzopen(filename, "r")) == NULL) {
		fprintf(stderr, "Can't open file %s\n", filename);
		exit(1);
	}

	char *fgets_check; /* this is to suppress a compiler warning*/
	while ((fgets_check = gzgets(fp, line, MAXLINELEN)) != NULL) {

		/* define our fastq data element */
		struct fastq *nfq;
		nfq = (struct fastq *) malloc(sizeof(*nfq));
		if (nfq == NULL) {
			fprintf(stderr, "Can't allocate memory for pointer\n");
			return 0;
		}

		chomp(line);
		// pop(line);

		/* store the whole line */
		nfq->info = dupstr(line);

		/* store the sequence ID */
		line[strcspn(line, " ")] = '\0';
		nfq->id = dupstr(line);

		/* read the sequence and save it */
		fgets_check = gzgets(fp, line, MAXLINELEN);
		if (line == NULL) {
			fprintf(stderr, "There was no sequence for %s", nfq->info);
			exit(1);
		}

		chomp(line);
		nfq->seq = dupstr(line);

		/* read the next line  and ignore it */
		fgets_check = gzgets(fp, line, MAXLINELEN);

		/* read the quality scores and save them */
		fgets_check = gzgets(fp, line, MAXLINELEN);
		if (line == NULL) {
			fprintf(stderr, "There were no quality scores for %s", nfq->info);
			exit(1);
		}
		chomp(line);
		nfq->qual = dupstr(line);

		if (add(nfq, "id", seqs) != NULL)
			seqcounter++;
		else
			fprintf(stderr, "We got an error adding %s\n", nfq->id);

	}

	gzclose(fp);

	return seqcounter;
}

