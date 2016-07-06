#include "ceeq_subsample.h"
#include <ceeq_fastq.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc <4) {
		fprintf(stderr, "Please provide some arguments on the command line. The first one should be the number of arguments to subsample\n");
		exit(1);
	}
	
	int n = atoi(argv[1]);
	if (!n) {
		fprintf(stderr, "Can't parse %s\n", argv[1]);
		fprintf(stderr, "Please provide some arguments on the command line. The first one should be the number of arguments to subsample\n");
		exit(1);
	}
	
	char **ss = subsample_n(argc, argv, n);
	for (int i=0;i<n; i++)
		printf("%d: %s\n", i, ss[i]);

}


