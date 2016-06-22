/*
 * A fast and memory efficient version of fastq pair that should allow us to pair data from SRA
 *
 * Author: Rob Edwards
 */

#include "fastq_pair_stream.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "%s [left reads] [right reads]\n", argv[0]);
		fprintf(stderr, "We take two files and find the reads that are paired and the reads that are unpaired in the files. Creating four output files\n");
		exit(1);
	}
	fastq_pair_stream(argv[1], argv[2]);
}
