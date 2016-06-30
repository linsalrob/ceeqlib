#
# This is a generic makefile for the ceeqlib project. 
# I started with the make file available from Tia Newhall:
# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html, but I have edited it heavily.
#
# You should start with that version. It doesn't have any of the errors that I have introduced!
#

# define the library name
LIBNAME = ceeq_fastq

# the name of the library
LIBLIB = lib$(LIBNAME)

# directory locations
SOURCEDIR = .
LIBDIR = ../lib
INCDIR = ../include
BINDIR = ../bin


# define the C source files

#SOURCES = $(wildcard $(SOURCEDIR)/*.c)
SOURCES = ceeq_hash_fastq.c \
	  ceeq_read_fastq.c \
	  ceeq_get_seqs.c

# define the C compiler to use
CC = gcc
# and the archiver
AR = ar

# define any compile-time flags
# -Wall enables all warning
#  -std=gnu99 is required to compile on centos which has an old compiler (apparently)
#
CFLAGS = -Wall -std=gnu99 -g -O3

# define any directories containing header files other than /usr/include
#
INCLUDES = -I$(HOME)/include  -I../include -Isrc -I$(INCDIR)

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -L$(HOME)/lib  -L../lib -L$(LIBDIR) -lz -L$(HOME)/Dropbox/GitHubs/ceeqlib/lib -lceeq_fastq -lceeq_dupstr

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like 
#LIBS = -lmylib -lm

# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SOURCES
# with the .o suffix
#

OBJS = $(SOURCES:.c=.o)

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean help install test


# the help menu
help:
	@echo "make file for the $(LIBNAME) library."
	@echo ""
	@echo "This will make a library (lib$(LIBNAME)) and install it."
	@echo "Currently the library will be installed in $(LIBDIR) and the header files in $(INCDIR)."
	@echo "Options:"
	@echo "		make $(LIBNAME) - make the library"
	@echo "		make test	- make the test suite"
	@echo "		make all	- make the library, install it, and make the test suite"
	@echo "		make clean	- remove the library and installation files"
	@echo "		make cleantest	- remove the compiled test suite
	@echo ""
	@echo "		make help	- show this help menu"


all: $(LIBNAME)

test:
	$(RM) $(SOURCEDIR)/test
	$(CC) $(CFLAGS) $(INCLUDES) -o test test.c $(LFLAGS)

install: |$(LIBDIR) $(INCDIR) $(LIBNAME)
	cp $(LIBLIB).a $(LIBDIR)
	cp $(LIBNAME).h $(INCDIR)


$(LIBNAME): $(OBJS)
	@echo Making $(LIBNAME)
	$(AR) cr $(LIBLIB).a $(OBJS)


$(BINDIR):
	mkdir -p $(BINDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(INCDIR):
	mkdir -p $(INCDIR)


# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) $(SOURCEDIR)/*.o $(SOURCEDIR)/*~ $(SOURCEDIR)/*.a $(INCDIR)/$(LIBNAME).h $(LIBDIR)/$(LIBLIB).a $(SOURCEDIR)/test

cleantest:
	$(RM) $(SOURCEDIR)/test
