# Compiler binary
CXX=g++
# Compiler options
CXXFLAGS=-Wall -O2 -std=c++0x
# The first target will be the default when make is called without arguments
all: exercise07.2
	rm -f *.o
exercise07.2:  exercise07.2.cc
# These are only for conveninience and are not strictly necessary
.PHONY: clean veryclean
clean: rm -f *.o
veryclean: clean
	rm -f *~
