# Compiler binary
CXX=g++
# Compiler options
CXXFLAGS=-Wall -O2 
# The first target will be the default when make is called without arguments
all: task_3_d task_3_e
	rm -f *.o
task_3_d: task_3_d.cc
task_3_e: task_3_e.cc
# These are only for conveninience and are not strictly necessary
.PHONY: clean veryclean
clean: rm -f *.o
veryclean: clean
	rm -f *~
