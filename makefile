#
# This is a generic makefile for the ceeqlib project. 
# I started with the make file available from Tia Newhall:
# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html, but I have edited it heavily.
#
# You should start with that version. It doesn't have any of the errors that I have introduced!
#


# define the executable file 
MAIN = ceeqlib
# I hate this name, so it is a place holder!
FQFAS = fastq2fasta_sorted
FQFA = fastq2fasta
FQPAIR = fastq_pair

SOURCEDIR = src
EXCDIR = bin

# define the C source files

SRCS = $(filter-out $(addprefix $(SOURCEDIR)/, fastq_pair_fast.c fastq2fasta_sorted.c fastq2fasta.c fastq_pair.c), $(wildcard $(SOURCEDIR)/*.c))
FQFASSRC = $(addprefix $(SOURCEDIR)/, $(FQFAS).c fastq_read.c fastq_hash.c ids.c hash.c)
FQFASRC = $(SOURCEDIR)/$(FQFA).c
FQPAIRSRC = $(addprefix $(SOURCEDIR)/, fastq_pair_fast.c fastq_pair_stream.c hash.c)

list:
	@echo Sources: $(SRCS)

listfqfasort:
	@echo Sources: $(FQFASSRC)

# define the C compiler to use
CC = gcc

# define any compile-time flags
CFLAGS = -Wall -std=gnu99 -g

# define any directories containing header files other than /usr/include
#
INCLUDES = -I$(HOME)/include  -I../include

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -L$(HOME)/lib  -L../lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like 
#LIBS = -lmylib -lm

# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)
FQFASORTOBJS = $(FQFASSRC:.c=.o)
FQFAOBJ = $(FQFASRC:.c=.o)
FQPAIROBJ = $(FQPAIRSRC:.c=.o)

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all: $(MAIN) $(FQFA) $(FQFAS) $(FQPAIR)

$(MAIN): | $(EXCDIR) $(OBJS)
	@echo Making $(MAIN)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXCDIR)/$(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

debug: $(OBJS)| $(EXCDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -g -o $(EXCDIR)/$(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

$(FQFAS): $(FQFASORTOBJS)| $(EXCDIR)
	@echo Making ceeq_$(FQFAS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXCDIR)/ceeq_$(FQFAS) $(FQFASORTOBJS) $(LFLAGS) $(LIBS)

$(FQFA): $(FQFAOBJ)| $(EXCDIR)
	@echo Making ceeq_$(FQFA)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXCDIR)/ceeq_$(FQFA) $(FQFAOBJ) $(LFLAGS) $(LIBS)

$(FQPAIR): $(FQPAIROBJ)| $(EXCDIR)
	@echo Making ceeq_$(FQPAIR)  
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXCDIR)/ceeq_$(FQPAIR) $(FQPAIROBJ) $(LFLAGS) $(LIBS)

$(EXCDIR):
	mkdir -p $(EXCDIR)


# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) $(SOURCEDIR)/*.o $(SOURCEDIR)/*~ $(EXCDIR)/$(MAIN) $(EXCDIR)/ceeq_$(FQFA) $(EXCDIR)/ceeq_$(FQFAS) $(EXCDIR)/ceeq_$(FQPAIR)

