# Compiler binary
CXX=g++
# Compiler options
CXXFLAGS=-Wall -O2 -std=c++0x
# The first target will be the default when make is called without arguments
#all: exercise08.1 exercise08.1b
all: exercise08.1b
	rm -f *.o
exercise08.1:  exercise08.1.cc 
exercise08.1b:  exercise08.1b.cc
# These are only for conveninience and are not strictly necessary
.PHONY: clean veryclean
clean: rm -f *.o
veryclean: clean
	rm -f *~
