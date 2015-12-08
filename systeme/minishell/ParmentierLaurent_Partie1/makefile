CC=gcc
CFLAGS=-W -Wall -pedantic -Werror -ansi

all:iutsh

iutsh:iutsh.o ligne_commande.o
	$(CC) $(CFLAGS) $^ -o $@

iutsh.o: iutsh.c iutsh.h
	$(CC) -c $(CFLAGS) $< -o $@

clear:
	rm -f iutsh.o iutsh
