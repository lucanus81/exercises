CC=g++
CFLAGS=-std=c++17 -g

all: check_brackets fill_region trees graphs fast_to_string compress_string

trees: trees.cpp
	$(CC) $(CFLAGS) -o trees trees.cpp

check_brackets: check_brackets.cpp
	$(CC) $(CFLAGS) -o check_brackets check_brackets.cpp

fill_region: fill_region.cpp
	$(CC) $(CFLAGS) -o fill_region fill_region.cpp

graphs: graphs.cpp
	$(CC) $(CFLAGS) -o graphs graphs.cpp

fast_to_string: fast_to_string.cpp
	$(CC) $(CFLAGS) -o fast_to_string fast_to_string.cpp

compress_string: compress_string.cpp
	$(CC) $(CFLAGS) -o compress_string compress_string.cpp

clean:
	rm check_brackets
	rm fill_region
	rm trees
	rm graphs
	rm fast_to_string
	rm compress_string
