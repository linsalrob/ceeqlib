/*
 * fastq_pair.c
 *
 * Given two fastq files write the sequences that are common and the sequences that are unique in each file.
 *
 */

#include "ceeqlib.h"
#include "fastq_read.h"
#include "fastq_hash.h"
#include "fastq_pair.h"
#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help(char s[]);
void recordseen(char s[], struct seenids *seen[]);

int main(int argc, char* argv[]) {
	if (argc < 3) {
		help(argv[0]);
		exit(0);
	}

	struct fastq *seqs1[HASHSIZE] = {NULL};
	fprintf(stderr, "Reading %s\n", argv[1]);
	read_fastq(argv[1], seqs1);

	struct fastq *seqs2[HASHSIZE] = {NULL};
	fprintf(stderr, "Reading %s\n", argv[2]);
	read_fastq(argv[2], seqs2);

	struct fastq *ptr1;
	struct fastq *ptr2;

	struct seenids *seen[HASHSIZE] = {NULL};


	/* file pointers to write to */
	FILE * left_paired;
	FILE * left_single;
	FILE * right_paired;
	FILE * right_single;


	/*
	 * Two ways to do this. Either via additional variables or directly. I chose directly.
	char *paired = ".paired.fq";
	char *single = ".single.fq";
	char *lpfn = strcat(dupstr(argv[1]), paired);
	char *rpfn = strcat(dupstr(argv[2]), paired);

	char *lsfn = strcat(dupstr(argv[1]), single);
	char *rsfn = strcat(dupstr(argv[2]), single);
	*/


	if ((left_paired = fopen(strcat(dupstr(argv[1]), ".paired.fq"), "w")) == NULL) {
		fprintf(stderr, "Can't open file %s\n", strcat(dupstr(argv[1]), ".paired.fq"));
		exit(1);
	}

	if ((left_single = fopen(strcat(dupstr(argv[1]), ".single.fq"), "w")) == NULL) {
		fprintf(stderr, "Can't open file %s\n", strcat(dupstr(argv[1]), ".single.fq"));
		exit(1);
	}

	if ((right_paired = fopen(strcat(dupstr(argv[2]), ".paired.fq"), "w")) == NULL) {
		fprintf(stderr, "Can't open file %s\n", strcat(dupstr(argv[2]), ".paired.fq"));
		exit(1);
	}

	if ((right_single = fopen(strcat(dupstr(argv[2]), ".single.fq"), "w")) == NULL) {
		fprintf(stderr, "Can't open file %s\n", strcat(dupstr(argv[2]), ".single.fq"));
		exit(1);
	}



	/* get the ids from file 1 and check if they are in file 2. If so, we print out both */
	for (int i=0; i< HASHSIZE; i++)
		for (ptr1 = seqs1[i]; ptr1 != NULL; ptr1 = ptr1->next) {
			char *id = ptr1->seqid;
			/* char *ori_id = dupstr(id); */
			int idx = strcspn(id, "/");
			if (idx < strlen(id)) {
				char rd = id[idx+1];
				if (rd == '1') {rd = '2';}
				else if (rd == '2') {rd = '1';}
				else {
					fprintf(stderr, "Error: can't figure out whether %c at position %d is /1 or /2\n", rd, idx);
					exit(-1);
				}
				id[idx+1] = rd;
			}
			else {
				fprintf(stderr, "%s does not appear to be from a paired end read. I expected it to have either /1 or /2\n", id);
				exit(-1);
			}
			int hashval = hash(ptr1->seqid);
			for (ptr2 = seqs2[hashval]; ptr2 != NULL; ptr2 = ptr2->next) 
				if (strcmp(ptr2->seqid, id) == 0) {
					fprintf(left_paired, "%s\n%s\n+\n%s\n", ptr1->name, ptr1->seq, ptr1->qual);
					fprintf(right_paired, "%s\n%s\n+\n%s\n", ptr2->name, ptr2->seq, ptr2->qual);
					recordseen(ptr2->seqid, seen);
				}
				else
					fprintf(left_single, "%s\n%s\n+\n%s\n", ptr1->name, ptr1->seq, ptr1->qual);
		}

	/* now we just need the ids from seq2 that we have seen and write them to right_single */
	for (int i=0; i< HASHSIZE; i++)
		for (ptr2 = seqs2[i]; ptr2 != NULL; ptr2 = ptr2->next) {
			/* check and see if we have seen this seqid, if not write it out */
			int notdone = 1;
			int hashval = hash(ptr2->seqid);
			struct seenids *seenptr;
			for (seenptr = seen[hashval]; seenptr != NULL; seenptr = seenptr->next)
				if (strcmp(seenptr->seqid, ptr2->seqid) == 0)
					notdone = 0; /* we have printed this so notdone = false */
			if (notdone)
				fprintf(right_single, "%s\n%s\n+\n%s\n", ptr2->name, ptr2->seq, ptr2->qual);
		}


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




}


void help(char s[]) {
	printf("%s [options] [fastq file 1] [fastq file 2]\n", s);
}


void recordseen(char s[], struct seenids *seen[]) {
	int hashval = hash(s);
	struct seenids *ptr;
	ptr = (struct seenids *) malloc(sizeof(*ptr));
	ptr->seqid = dupstr(s);
	ptr->next = seen[hashval];
	seen[hashval]=ptr;
}
	
