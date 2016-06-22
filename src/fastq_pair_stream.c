/*
 * A streaming version of fastq pair. This uses slightly less than 1/3 the space of the previous version.
 *
 * Essentially, we have two improvements:
 * 	1. We add a flag to the struct fastq to tell whether it has been printed already, so we only need an additional int there
 * 	2. We only store the sequence information from the first file, and stream the information from the second file.
 *
 * We could also save more memory by only storing the IDs from the first file, but that would require two passes through that file.
 */

#include "fastq_pair_stream.h"
#include "hash.h"
#include "dupstr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* our hash of sequences from the left file */
struct fastq_pair_stream *seqs[HASHSIZE] = {NULL};

char *ignored; /* this variable is not used, it suppresses a compiler warning */
/* stream the fastq files.
 * left_fn: the file name for the file with the left reads (/1)
 * right_fn: the file name for the file with the right reads (/2)
 */

int fastq_pair_stream(char *left_fn, char *right_fn) {
	

	/* 
	 * read the left fastq file and store it in seqs 
	 * We can't use our normal read here because our
	 * struct is slightly different
	 */

	FILE *fp;

	char line[MAXLINELEN];
	int seqcounter=0;

	if ((fp = fopen(left_fn, "r")) == NULL) {
		fprintf(stderr, "Can't open file %s\n", left_fn);
		exit(1);
	}

	while ((ignored = fgets(line, MAXLINELEN, fp)) != NULL) {

		/* define our fastq data element */
		struct fastq_pair_stream *nfq;
		nfq = (struct fastq_pair_stream *) malloc(sizeof(*nfq));
		if (nfq == NULL) {
			fprintf(stderr, "Can't allocate memory for pointer\n");
			return 0;
		}
		nfq->seen = 0;

		/* store the whole line */
		nfq->name = dupstr(line);

		/* store the sequence ID */
		line[strcspn(line, " ")] = '\0';
		nfq->seqid = dupstr(line);

		/* read the sequence and save it */
		ignored = fgets(line, MAXLINELEN, fp);
		if (line == NULL) {
			fprintf(stderr, "There was no sequence for %s", nfq->name);
			exit(1);
		}
		nfq->seq = dupstr(line);

		/* read the next line  and ignore it */
		ignored = fgets(line, MAXLINELEN, fp);

		/* read the quality scores and save them */
		ignored = fgets(line, MAXLINELEN, fp);
		if (line == NULL) {
			fprintf(stderr, "There were no quality scores for %s", nfq->name);
			exit(1);
		}
		nfq->qual = dupstr(line);

		if (addfqs(nfq) != NULL)
			seqcounter++;

		free(nfq);

	}

	if (ferror(fp)) {
		fprintf(stderr, "There was an error (%d) reading %s\n", ferror(fp), left_fn);
		exit(1);
	}
	
	fclose(fp);

	/* now we want to open output files for left_paired, right_paired, and right_single */



	FILE * left_paired;
	FILE * left_single;
	FILE * right_paired;
	FILE * right_single;
	
	char *lpfn = strcat(dupstr(left_fn), ".paired.fq");
	char *rpfn = strcat(dupstr(right_fn), ".paired.fq");
	char *lsfn = strcat(dupstr(left_fn), ".single.fq");
	char *rsfn = strcat(dupstr(right_fn), ".single.fq");
	printf("Writing the paired reads to %s and %s.\nWriting the single reads to %s and %s\n", lpfn, rpfn, lsfn, rsfn);

	if ((left_paired = fopen(lpfn, "w")) == NULL ) {
		fprintf(stderr, "Can't open file %s\n", lpfn);
		exit(1);
	}

	if ((left_single = fopen(lsfn, "w")) == NULL) {
		fprintf(stderr, "Can't open file %s\n", lsfn);
		exit(1);
	}
	if ((right_paired = fopen(rpfn, "w")) == NULL) {
		fprintf(stderr, "Can't open file %s\n", rpfn);
		exit(1);
	}

	if ((right_single = fopen(rsfn, "w")) == NULL) {
		fprintf(stderr, "Can't open file %s\n", rsfn);
		exit(1);
	}


	/* now we want to iterate through the right file, and print the reads to either paired or singles */


	if ((fp = fopen(right_fn, "r")) == NULL) {
		fprintf(stderr, "Can't open file %s\n", right_fn);
		exit(1);
	}

	while ((ignored = fgets(line, MAXLINELEN, fp)) != NULL) {
		
		/* store the whole line */
		char *name = dupstr(line);

		/* store the sequence ID */
		line[strcspn(line, " ")] = '\0';
		char *seqid = dupstr(line);

		/* read the sequence and save it */
		ignored = fgets(line, MAXLINELEN, fp);
		if (line == NULL) {
			fprintf(stderr, "There was no sequence for %s", name);
			exit(1);
		}
		char *seq = dupstr(line);

		/* read the next line  and ignore it */
		ignored = fgets(line, MAXLINELEN, fp);

		/* read the quality scores and save them */
		ignored = fgets(line, MAXLINELEN, fp);
		if (line == NULL) {
			fprintf(stderr, "There were no quality scores for %s", name);
			exit(1);
		}
		char *qual = dupstr(line);

		/* figure out if the read has been seen before */

		int idx = strcspn(seqid, "/");
		if (idx < strlen(seqid)) {
			char rd = seqid[idx+1];
			if (rd == '1') {rd = '2';}
			else if (rd == '2') {rd = '1';}
			else {
				fprintf(stderr, "Error: can't figure out whether %c at position %d is /1 or /2\n", rd, idx);
				exit(-1);
			}
			seqid[idx+1] = rd;
		}
		else {
			fprintf(stderr, "%s does not appear to be from a paired end read. I expected it to have either /1 or /2\n", seqid);
			exit(-1);
		}
		
		int hashval = hash(seqid);
		int found = 0;
		struct fastq_pair_stream *ptr;
		for (ptr = seqs[hashval]; ptr != NULL; ptr = ptr->next)
			if (strcmp(ptr->seqid, seqid) == 0) {
				ptr->seen = 1;
				found = 1;
				fprintf(left_paired, "%s\n%s\n+\n%s\n", ptr->name, ptr->seq, ptr->qual);
				fprintf(right_paired, "%s\n%s\n+\n%s\n", name, seq, qual);
			}
		if (!found)
			fprintf(right_single, "%s\n%s\n+\n%s\n", name, seq, qual);
	}
	/* now we just need to iterate through all the sequences and print the ones we haven't seen */


	struct fastq_pair_stream *ptr;
	for (int i=0; i<HASHSIZE; i++) 
		for (ptr = seqs[i]; ptr != NULL; ptr = ptr->next)
			if (!ptr->seen)
				fprintf(left_single, "%s\n%s\n+\n%s\n", ptr->name, ptr->seq, ptr->qual);



		
	/* error check and clean up */
	if (ferror(left_paired))
		fprintf(stderr, "WARNING: THERE WAS AN ERROR WRITING TO THE LEFT PAIRED FILE. Check it out. The error code is %d", ferror(left_paired));
	fclose(left_paired);

	if (ferror(right_paired))
		fprintf(stderr, "WARNING: THERE WAS AN ERROR WRITING TO THE RIGHT PAIRED FILE. Check it out. The error code is %d", ferror(right_paired));
	fclose(right_paired);


	if (ferror(left_single))
		fprintf(stderr, "WARNING: THERE WAS AN ERROR WRITING TO THE LEFT SINGLES FILE. Check it out. The error code is %d", ferror(left_single));
	fclose(left_single);

	if (ferror(right_single))
		fprintf(stderr, "WARNING: THERE WAS AN ERROR WRITING TO THE RIGHT SINGLES FILE. Check it out. The error code is %d", ferror(right_single));
	fclose(right_single);

	return seqcounter;

}





/* add a sequence to the hash.
 *
 * struct fastq *s is our fastq structure
 * seqs is a pointer to an array of structs that is our hash
 *
 * Notice that in this hash we don't check for duplicates. We store
 * everything.
 */

struct fastq_pair_stream *addfqs(struct fastq_pair_stream *s) {
	struct fastq_pair_stream *ptr;
	unsigned hashval;

	ptr = (struct fastq_pair_stream *) malloc(sizeof(*ptr));
	if (ptr == NULL) {
		fprintf(stderr, "Can't allocate memory for pointer\n");
		return NULL;
	}

	if (((ptr->seqid = dupstr(s->seqid)) == NULL) ||
			((ptr->seq = dupstr(s->seq)) == NULL) ||
			((ptr->name = dupstr(s->name)) == NULL) ||
			((ptr->qual = dupstr(s->qual)) == NULL)) {
		fprintf(stderr, "Can't duplicate struct\n");
		return NULL;
	}

	/* this is an add first */
	hashval = hash(s->seqid);
	ptr->next = seqs[hashval];
	seqs[hashval] = ptr;

	return ptr;
}


