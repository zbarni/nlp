# Compiler binary
CXX=g++
# Compiler options
CXXFLAGS=-Wall -O2 -std=c++0x
# The first target will be the default when make is called without arguments
all: exercise11
	rm -f *.o
exercise11:  exercise11.cc
# These are only for conveninience and are not strictly necessary
.PHONY: clean veryclean
clean: rm -f *.o
veryclean: clean
	rm -f *~
