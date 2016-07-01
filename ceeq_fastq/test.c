
#include <ceeq_fastq.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>

/*
 * A test suite for reading fastq files. This tests all of the methods that we have written 
 *
 */

#define ESEQS 5 // the number of sequences we expect to find in the file!


#define TESTPRINT 0 // this is a boolean that determines whether we test printing fastq and fasta sequences. You can leave this set to 0 



int main(int argc, char *argv[]) {
	// this file has 5 sequences in it so it should be easy to read!
	char *filename = "../example_data/small.fastq";
	struct fastq *seqs[HASHSIZE] = {NULL};
	int nseqs = read_fastq(filename, seqs);
	int error = 0;
	if (nseqs != ESEQS) {
		fprintf(stderr, "There was an error reading %s. We retrieved %d sequences but should have found %d sequences\n", filename, nseqs, ESEQS);
		error = 1;
	}

	/* now test the get sequence methods */
	int nnseqs = number_of_sequences(seqs);
	if (nnseqs != ESEQS) {
		printf("There was an error checking the number of sequences. We found %d using number_of_sequences but it should be %d\n", nnseqs, ESEQS);
		error++;
	}

	/* test getting the ids */
	char *ids[nnseqs];
	nnseqs = get_ids(ids, seqs);
	printf("Got %d ids\n", nnseqs);
	for (int i=0; i<nnseqs; i++)
		printf("ID %d: %s\n", i, ids[i]);
	

	char *sq = get_sequence("@GFH7CG303FQFE8/1", seqs);
	char *sqans = "AAATACGGGTAGATATACCGCCATGTCTCGCAAACAGCCTCATCATGCCGCGCCTGCCCACTTTTTTGCATCAGTATCCCGGCATTGCGCTGGAACTTTGTAGTAGCGATCGACAGGTCGATTTACTACGGGAAGATTTCGACTGCGTGGTGCGCACAGAGCCGCTACATGCGCCAGGGATACTGACGCGCCCGCTTGGCAAACTGAGAAGAGTGAACTGCGCCAGCCCACAATACCTGGCGCGCTTTGGGTAATCCAGAAAAACCTTGACGATCTCGCCTCACATGCGGTGGTGCATTATTCATTGACCCCGGGAGTTTCTTCACCGGGTTTTGCCTTTGAAACTCCCACGGTATGCAGTGGTAAAAAACCGGCGGAAATGCTAACGGTAAACAGTACGAGACTTGGCATACAGCCTG";
	char *quans = "@@@DDDDDFFFIIIIIIIIIIIIIIIIIIIIHHHIIFDDHHHHHHHHHHHHHFFFFFFFFF666666FFFFFFFFFFFFFCCADDDFDDCDDDDDD???6388CFFCCCCCDFFFFFDFFFF??8638<FF?AA>DFFFAA<<<FFFFFAACCFF???CFDDDDBBBBBBA<<889;888<<===BBBBB=;;A688<<9...3<4434443<<AAAAA??A==<>8624/2642..028>=<9989<<;4/..6;;<:,,,--..<<==:9<<<A<4444<=<<733224000<><8::CGGDDDDB::99400/0444322576;622....266666<68899444:8A?\?\?=>>>:3//.------55--266...3777666646...6297...269766///3:<><>;;93";
	if (sq == NULL) {
		fprintf(stderr, "Bugger, no sequence for @GFH7CG303FQFE8/1\n");
		error++;
	}

	if (strcmp(sq, sqans)) {
		error++;
		printf("The sequence we retrieved for @GFH7CG303FQFE8/1 appeared to be wrong:\n%s\n", sq);
	}

	sq = get_sequence("NOSEQ", seqs);
	if (sq != NULL) {
		fprintf(stderr, "Using ID NOSEQ we retrieved %s\n", sq);
		error++;
	}


	char *qual = get_quality("@GFH7CG303FQFE8/1", seqs);
	if (strcmp(qual, quans)) {
		fprintf(stderr, "The quality scores for @GFH7CG303FQFE8/1 do not appear correct\n");
		error++;
	}

	qual = get_quality("NOSEQ", seqs);
	if (qual != NULL) {
		fprintf(stderr, "Got %s as quality scores for NOSEQ but shouldn't find any!\n", qual);
		error++;
	}

	if (TESTPRINT) {
		printf("Printing the sequences\n");
		print_fastq(seqs);
		printf("\n\n");
		print_fasta(seqs);
	}


	
	if (error) 
		fprintf(stderr, "There were %d errors when running the tests\n", error);
	else
		fprintf(stderr, "All tests passed\n");


	exit(error);

}
