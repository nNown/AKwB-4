CXX = g++
CPPFLAGS = -Wall -Wextra -Wno-unused-parameter -Iinclude/ -Og -g -std=c++2a

all: main

main: src/main.cpp src/instance_parser.cpp src/instance_generator.cpp
	$(CXX) $(CPPFLAGS) -o $@ $^ -lstdc++fs