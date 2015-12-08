DEBUG=1

OBJDIR=./obj
BINDIR=./bin
SRCDIR=./src
INCDIR=./inc

CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -std=c99 -I $(INCDIR) -DDEBUG_AFFICHE=$(DEBUG)

.PHONY : tests clear distclear

tests: $(BINDIR)/test_lifo
	$(BINDIR)/test_lifo

$(BINDIR)/test_lifo: $(SRCDIR)/test_lifo.c $(OBJDIR)/lifo.o
	$(CC) $(CFLAGS) $^ -o $@

# objets

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# autres regles

clear:
	rm -f $(OBJDIR)/*.o

distclear: clear
	rm -f $(BINDIR)/*
