#include "ceeq_fastq_pair.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc < 3) {
		help();
		exit(0);
	}

	fastq_pair_stream(argv[1], argv[2]);

}

void help() {
	printf("ceeqlib.c\nVersion %f\nCopyright Rob Edwards\rReleased under the MIT license\n\n", VERSION);
	printf("pair the left and right reads, creating left_paired, right_paired, left_single, and right_single files\n");
	printf("Usage: %s [fastq file of left reads] [fastq file of right reads]", argv[0]);
	exit(0);
}
	
