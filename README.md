# ceeqlib
ceeqlib (pronounced seq-lib) is a library written in C for manipulating fastq and fasta files.

ceeqlib is written in pure C using only the standard library to ensure portability among machines. See the Installation section.

# ceeqlib libraries

Our libraries are split into core functions and sequence related functions. ceeqlib is designed to be standalone and to compile with vanilla C installations.

##core libraries##
* *ceeq_arr* has functions for manipulating arrays, including shuffling elements in an array and swapping elements in an array. [ceeq_arr/ceeq_arr.h](ceeq_arr.h)
* *ceeq_str* has functions for manipulating strings, including duplicating, concatenating and removing new lines. [ceeq_str/ceeq_str.h](ceeq_str.h)

* *ceeq_fastq* has functions for reading fastq files and returning hashes of DNA sequences. You can [ceeq_fastq](read more) about the sequence 
format or read [ceeq_fastq.h](ceeq_fastq/ceeq_fastq.h)



ceeq_count  ceeq_fastq_pair  ceeq_lib  ceeq_str  ceeq_subsample

