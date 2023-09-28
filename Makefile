###
### Makefile for gerp Project
###
### Author: Ben Silver and Joel MacVicar 

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -O2 -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

gerp: main.o gerp.o wordHash.o stringProcessing.o DirNode.o FSTree.o
	$(CXX) $(LDFLAGS) -o gerp main.o gerp.o wordHash.o stringProcessing.o DirNode.o FSTree.o

treeTraversal: FSTreeTraversal.o DirNode.o FSTree.o
	$(CXX) $(LDFLAGS) -o treeTraversal FSTreeTraversal.o DirNode.o FSTree.o

main.o: main.cpp gerp.h
	$(CXX) $(CXXFLAGS) -c main.cpp

gerp.o: gerp.cpp gerp.h wordHash.h stringProcessing.h FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c gerp.cpp

wordHash.o: wordHash.cpp wordHash.h stringProcessing.h
	$(CXX) $(CXXFLAGS) -c wordHash.cpp

FSTreeTraversal.o: FSTreeTraversal.cpp
	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp

stringProcessing.o: stringProcessing.cpp stringProcessing.h 
	$(CXX) $(CXXFLAGS) -c stringProcessing.cpp

unit_test: unit_test_driver.o DirNode.o FSTree.o stringProcessing.o wordHash.o gerp.o
	$(CXX) $(CXXFLAGS) $^

provide_phase1:
	provide comp15 proj4_gerp_phase1 FSTreeTraversal.cpp \
					stringProcessing.h \
					stringProcessing.cpp \
					README

provide_final:
	provide comp15 proj4_gerp README Makefile \
							gerp.h gerp.cpp \
							wordHash.h wordHash.cpp\
							stringProcessing.h stringProcessing.cpp \
							main.cpp unit_tests.h \
							DirNode.h FSTree.h \
							test1_ref.out test1_us.out test1.txt


							

							