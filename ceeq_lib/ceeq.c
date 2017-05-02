/*
 * The main ceeq program that handles reading and writing files
 * based on command line flags.
 *
 * Author: Rob Edwards
 *
 */

#include "ceeq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		print_usage(argv[0]);
		exit(0);
	}


	// some flags we can set
	// 0 means not set or unlimited
	int fasta_output = 0;
	int nseqs_to_print = 0;

	int i=1;
	while (i<argc) {
		if (!strcmp(argv[i], "-h")) {
			print_help(argv[0]);
			exit(0);
		} else if (!strcmp(argv[i], "-a")) {
			fasta_output = 1;
		} else if (!strcmp(argv[i], "-n")) {
			nseqs_to_print = atoi(argv[++i]);
		} else {
			printf("Unknown option '%s'\n", argv[i]);
		}
		i++;
	}
}



/*
 * print the help message, including usage options
 * for ceeq
 */

void print_help(char *name) {
	printf("%s\n", name);
	printf("ceeq library\n"
			"============\n\n"
			"The ceeq library is a library for manipulating DNA sequences written in C. "
			"The goal is to generate a library that is fast to handle the sequences, "
			"available and extensible, and written with a simple logic so you can understand "
			"how the components of the library work.\n\n"
			"To use the ceeq standalone application, please provide one of the flags below. "
			"For most options you can either provide a file name on the command line, or use "
			"a - to read from stdin (e.g. from pipes, etc). ceeq will automatically try and "
			"guess the file format that you are using. We currently only support fastq and "
			"fasta, but maybe we'll add others when we get there.\n\n"
			"Current options:\n"
			"================\n\n"
			"Output selection\n"
			"-n number of sequences to print\n"
			"\nOutput format\n"
			"The default format is fastq\n"
			"-a print output in fasta format\n"
	      );
}

/*
 * Print a brief usage message to remind the user of the options
 */

void print_usage(char *name) {
	printf("%s [-h -n number] sequence file\n", name);
	printf("-h print a detailed help\n"
			"-n print n sequences from the file\n"
			"-a print the output in fasta format (the default is fastq)\n"
	      );
}


