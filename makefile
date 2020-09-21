CC=g++
CFLAGS=-std=c++17 -g

all: check_brackets fill_region

check_brackets: check_brackets.cpp
	$(CC) -o check_brackets check_brackets.cpp

fill_region: fill_region.cpp
	$(CC) -o fill_region fill_region.cpp

clean:
	rm check_brackets
	rm fill_region
