CC=g++
CFLAGS=-std=c++17 -g

all: check_brackets fill_region trees

trees: trees.cpp
	$(CC) $(CFLAGS) -o trees trees.cpp

check_brackets: check_brackets.cpp
	$(CC) $(CFLAGS) -o check_brackets check_brackets.cpp

fill_region: fill_region.cpp
	$(CC) $(CFLAGS) -o fill_region fill_region.cpp

clean:
	rm check_brackets
	rm fill_region
	rm trees
