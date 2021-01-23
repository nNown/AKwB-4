CXX = g++
CPPFLAGS = -Wall -Wextra -Wno-unused-parameter -Iinclude/ -O3 -std=c++2a

all: main

main: src/main.cpp src/instance_parser.cpp src/instance_generator.cpp src/instance.cpp
	$(CXX) $(CPPFLAGS) -o $@ $^ -lstdc++fs