# Compiler binary
CXX=g++
# Compiler options
CXXFLAGS=-Wall -O2 -std=c++0x
# The first target will be the default when make is called without arguments
all: exercise03.1
	rm -f *.o
exercise03.1: trie.o dictionary.o exercise03.1.cc
dictionary.o: dictionary.cc dictionary.hh
trie.o: trie.cc trie.hh
# These are only for conveninience and are not strictly necessary
.PHONY: clean veryclean
clean: rm -f *.o
veryclean: clean
	rm -f *~
