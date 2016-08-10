
/*
 * convert a fastq file to fasta.
 * This is a fast method that just counts lines and does not store the
 * file in memory.
 *
 * It is basically a one off program because it doesn't use any of our 
 * data structures.
 *
 */

#include <stdio.h>
#include <zlib.h>

#define MAXLINELINE 10000

void fastq2fasta(char *inputfile, int input_is_compressed, char *outputfile, int output_is_compressed) {
	FILE *inp;
	FILE *outp;
	gzFile cinp;
	gzFile goutp;

	char *line = malloc(sizeof(char) * MAXLINELEN + 1);

	if (input_is_compressed) {
		if ((cinp = gzopen(inputfile, "r")) == NULL) {
			fprintf(stderr, "Can't open compressed input file %s\n", inputfile);
					                exit(1);
							        }

	        char *fgets_check; /* this is to suppress a compiler warning*/
		        while ((fgets_check = gzgets(fp, line, MAXLINELEN)) != NULL) {




  if ( argc < 3) {
    cerr << "Usage: " << argv[0] << " <fastq file (use - to read from STDIN)> <fasta file>\n";
    return 1;
  }


  ifstream fastq;
  streambuf* orig_cin = 0;
  if (strcmp(argv[1], "-") != 0) {
    cout << "reading from " << argv[1] << '\n';
    fastq.open(argv[1]);
    if (!fastq) return 1;
    orig_cin = cin.rdbuf(fastq.rdbuf());
    cin.tie(0); // tied to cout by default
  }

  string line;
  ofstream fasta(argv[2]);
  if (!fasta) return 2;
  int c=0;
  
  while (getline(cin, line))
  {
    //cout << c << " : " << line << '\n';
    if ( c==0 ) {
      line.replace(0, 1, ">");
      fasta << line << '\n';
    }
    if ( c==1 ) {
      fasta << line << '\n';
    }
    c++;
    if ( c == 4) { c=0 ;}
  }

  return 0;
}
