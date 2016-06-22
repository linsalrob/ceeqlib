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
	bin/ceeq_fastq_pair_gz

```

See Getting Started for more information on using ceeqlib.

# What the programs do

The current programs in the ceeq library are:

1. `ceeq_fastq2fasta`: convert a fastq file to a fasta file
2. `ceeq_fastq2fasta_sorted`: read a fastq file, sort the sequences and print the output as fasta
3. `ceeq_fastq_pair`: take two fastq files and find the intersection and differences. The input is two files, left.fastq and right.fastq (you can call these what ever you want) and the output is four files: left.fastq.paired.fq and right.fastq.paired.fq have the paired sequences in the same order in each file; left.fastq.single.fq and right.fastq.single.fq have the unpaired sequences from each file respectively.
4. `ceeq_fastq_pair_gz`: take two gzipped fastq files and find the intersection and differences. This is the same as ceeq_fastq_pair however the input is two gzip compressed files.
