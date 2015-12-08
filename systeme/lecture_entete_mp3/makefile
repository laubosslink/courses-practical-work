CC=gcc
CFLAGS=-W -Wall -pedantic -Werror -ansi

all:main

main:main.o tag.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c tag.h
	$(CC) -c $(CFLAGS) $< -o $@

tag.o: tag.c tag.h
	$(CC) -c $(CFLAGS) $< -o $@

clear:
	rm -f main.o tag.o main
