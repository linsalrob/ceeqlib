#
# This is a generic makefile for the ceeqlib project. 
# I started with the make file available from Tia Newhall:
# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html, but I have edited it heavily.
#
# You should start with that version. It doesn't have any of the errors that I have introduced!
#


# directory locations
SOURCEDIR = .
LIBDIR = lib
INCDIR = include
BINDIR = bin


.PHONY: clean all test help ceeq_str ceeq_arr ceeq_fastq ceeq_subsample

# the help menu
help:
	@echo "make file for ceeq_lib"
	@echo ""
	@echo "This is the top level make file that just recursively runs make through all the parts of the library"
	@echo "Options:"
	@echo "		make all	- make all the parts of the library except the test suite"
	@echo "		make test	- make the test suite"
	@echo "		make clean	- remove the library and installation files"
	@echo ""
	@echo "		make help	- show this help menu"


all: ceeq_subsample

ceeq_str:
	$(MAKE) -C ceeq_str install

ceeq_arr:
	$(MAKE) -C ceeq_arr install

ceeq_fastq: ceeq_str
	$(MAKE) -C ceeq_fastq install

ceeq_subsample: ceeq_fastq ceeq_arr
	$(MAKE) -C ceeq_subsample install



#example_data  include  lib  LICENSE  makefile  README.md  src  tests




clean:
	$(RM) $(SOURCEDIR)/*.o $(SOURCEDIR)/*~ $(SOURCEDIR)/*.a $(INCDIR)/*.h $(LIBDIR)/*.a $(SOURCEDIR)/test/test

