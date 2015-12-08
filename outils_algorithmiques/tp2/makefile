CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -std=c99

.PHONY : all clear 

all : abr

abr: main.o abr.o file.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c 
	$(CC) $(CFLAGS) -c $< -o $@

abr.o: abr.c 
	$(CC) $(CFLAGS) -c $< -o $@

file.o: file.c 
	$(CC) $(CFLAGS) -c $< -o $@

clear: 
	rm -f *.o
