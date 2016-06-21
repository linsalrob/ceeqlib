/*
 * Convert a fastq file to fasta. This preserves the order of the sequences in the fastq file
 */


#include <stdio.h>
#include <stdlib.h>

#define MAXLINELEN 10000

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("%s [fastq file]\n", argv[0]);
		exit(1);
	}

	FILE * fp;

	char line[MAXLINELEN];

	if ((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Can't open file %s\n", argv[1]);
		exit(1);
	}

	int counter = 0;

	while ((fgets(line, MAXLINELEN, fp)) != NULL) {
		if (counter == 0) {
			/* header line, so convert @ to > */
			line[0] = '>';
			printf("%s", line);
		}
		if (counter == 1) {
			printf("%s", line);
		}
		counter++;
		if (counter == 4) {counter = 0;}
	}
	fclose(fp);
	return 0;
}


