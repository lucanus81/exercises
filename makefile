CC=g++
CFLAGS=-std=c++17 -g

check_brackets: check_brackets.cpp
	$(CC) -o check_brackets check_brackets.cpp

clean:
	rm check_brackets
