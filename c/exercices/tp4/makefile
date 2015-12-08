CC=gcc
#CFLAGS=-W -pedantic -Wall -Werror

all:main

main: main.o exercice1_a.o exercice1_b.o exercice2_a.o exercice2_c.o exercice2_d.o exercice3.o swap.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $@

exercice1_a.o: exercice1_a.c
	$(CC) -c $(CFLAGS) $< -o $@

exercice1_b.o: exercice1_b.c swap.o
	$(CC) -c $(CFLAGS) $< -o $@

exercice2_a.o: exercice2_a.c
	$(CC) -c $(CFLAGS) $< -o $@

exercice2_c.o: exercice2_c.c
	$(CC) -c $(CFLAGS) $< -o $@

exercice2_d.o: exercice2_d.c 
	$(CC) -c $(CFLAGS) $< -o $@

exercice3.o: exercice3.c
	$(CC) -c $(CFLAGS) $< -o $@

swap.o: swap.c
	$(CC) -c $(CFLAGS) $< -o $@

clear:
	rm -f exercice?.o main
