CC=gcc
CFLAGS=-W -pedantic -Wall -Werror

#all: exercice1 exercice2 exercice3 exercice4 exercice5 exercice6 main

all:main

main: main.o exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c main.h
	$(CC) -c $(CFLAGS) $< -o $@

exercice1.o: exercice1.c
	$(CC) -c $(CFLAGS) $< -o $@

exercice2.o: exercice2.c
	$(CC) -c $(CFLAGS) $< -o $@

exercice3.o: exercice3.c
	$(CC) -c $(CFLAGS) $< -o $@

exercice4.o: exercice4.c
	$(CC) -c $(CFLAGS) $< -o $@

exercice5.o: exercice5.c
	$(CC) -c $(CFLAGS) $< -o $@

exercice6.o: exercice6.c
	$(CC) -c $(CFLAGS) $< -o $@

#exercice2: exercice2.c
#	$(CC) $< -o $@.o
#exercice3: exercice3.c
#	$(CC) $< -o $@.o
#exercice4: exercice4.c
#	$(CC) $< -o $@.o
#exercice5: exercice5.c
#	$(CC) $< -o $@.o
#exercice6: exercice6.c
#	$(CC) $< -o $@.o
clear:
	rm -f exercice?.o main
