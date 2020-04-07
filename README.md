[![Edwards Lab](https://img.shields.io/badge/Bioinformatics-EdwardsLab-03A9F4)](https://edwards.sdsu.edu/research)

# ceeqlib
ceeqlib (pronounced seq-lib) is a library written in C for manipulating fastq and fasta files.

ceeqlib is written in pure C using only the standard library to ensure portability among machines. See the Installation section.



# ceeqlib libraries

Our libraries are split into core functions and sequence related functions. ceeqlib is designed to be standalone and to compile with vanilla C installations.

##core libraries##
* *ceeq_arr* has functions for manipulating arrays, including shuffling elements in an array and swapping elements in an array. [ceeq_arr.h](ceeq_arr/ceeq_arr.h)
* *ceeq_str* has functions for manipulating strings, including duplicating, concatenating and removing new lines. [ceeq_str.h](ceeq_str/ceeq_str.h)

* *ceeq_fastq* has functions for reading fastq files and returning hashes of DNA sequences. You can [read more](ceeq_fastq) about the sequence 
format or read [ceeq_fastq.h](ceeq_fastq/ceeq_fastq.h)

* *ceeq_fastq_pair* has functions for checking paired files to see which reads are pairs and which are singletons. [ceeq_fastq_pair.h](ceeq_fastq_pair.h)

* *ceeq_lib*  has global parameters for the library (currently only the version number!)

* *ceeq_subsample* subsample a fastq file and print a required number of sequences.

* *ceeq_count* count the characters or sequences in a fastq file and summarize them.

