
#include <ceeq_subsample.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "%s <number of sequences> <fastq file>\n", argv[0]);
		exit(1);
	}

	int n = subsample(atoi(argv[1]), argv[2]);
	fprintf(stderr, "%d sequences were found\n", n);
}



