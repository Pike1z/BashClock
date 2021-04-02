# Makefile for Time program
# Made by Charlie Ringler

all : *.c
	gcc -pedantic -g -o Time $^

%o : %c
	gcc -pedantic -o $@ -c $^
