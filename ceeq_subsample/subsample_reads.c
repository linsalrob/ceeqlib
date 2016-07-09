
#include <ceeq_subsample.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "%s [-c compressed input file] <number of sequences> <fastq file>\n", argv[0]);
		exit(1);
	}

	int nseqs = 0;
	int compressed = 0;
	char *fname="";
	// should be using getopts here....
	if (!strcmp(argv[1], "-c")) {
		compressed = 1;
		nseqs = atoi(argv[2]);
		fname = argv[3];
	} else {
		nseqs = atoi(argv[1]);
		fname = argv[2];
	}



	int n = subsample(nseqs, fname, compressed);
	fprintf(stderr, "%d sequences were found\n", n);
}



