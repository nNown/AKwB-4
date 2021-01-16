CXX = g++
CPPFLAGS = -Wall -Wextra -Wno-unused-parameter -Iinclude/ -O3 -std=c++2a

all: main

main: src/main.cpp src/graph.cpp src/fasta.cpp src/fasta_parser.cpp
	$(CXX) $(CPPFLAGS) -o $@ $^