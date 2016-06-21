# ceeqlib
ceeqlib (pronounced seq-lib) is a library written in C for manipulating fastq and fasta files.

ceeqlib is written in pure C using only the standard library to ensure portability among machines. See the Installation section.


# Getting started

There are three ways to use ceeqlib:

1. You can use the ceeqlib command, and then specify a command to run (e.g. `ceeqlib fastq2fasta`)
2. You can run the individual programs in ceeqlib (e.g. `bin/ceeq_fastq2fasta`)
3. You can incorporate ceeqlib in your own libraries.


Please post any issues on GitHub and we'll fix them.




# Installation

Clone ceeqlib from GitHub using 

``` git clone https://github.com/linsalrob/ceeqlib.git ```

then enter the ceeqlib directory

``` cd ceeqlib ```

Compile the code

``` make clean && make all ```

The executables are in `bin/`. You should then be able to use ceeqlib:

``` bin/ceeqlib ```

or one of the individual commands:

``` 
	bin/ceeq_fastq2fasta  
	bin/ceeq_fastq2fasta_sorted 
	bin/ceeq_fastq_pair 

```

See Getting Started for more information on using ceeqlib.


