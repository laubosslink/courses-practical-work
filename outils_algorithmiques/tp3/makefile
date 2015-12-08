DEBUG=1

OBJDIR=./obj
BINDIR=./bin
SRCDIR=./src
INCDIR=./inc

CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -std=c99 -I $(INCDIR) -DDEBUG_AFFICHE=$(DEBUG) -DDEBUG_OPTIMISE=0

.PHONY : all abr tests clear distclear

all : abr

abr: main.o abr.o
	$(CC) $^ -o $@

# tests 

tests: $(BINDIR)/test_recherche $(BINDIR)/test_insertion $(BINDIR)/test_chargement
	$(BINDIR)/test_recherche
	$(BINDIR)/test_insertion
	$(BINDIR)/test_chargement
	
$(BINDIR)/test_recherche: $(OBJDIR)/test_recherche.o $(OBJDIR)/abr.o
	$(CC) $^ -o $@
	
$(BINDIR)/test_insertion: $(OBJDIR)/test_insertion.o $(OBJDIR)/abr.o
	$(CC) $^ -o $@

$(BINDIR)/test_chargement: $(OBJDIR)/test_chargement.o $(OBJDIR)/abr.o
	$(CC) $^ -o $@
	
# objets

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

# autres regles

clear: 
	rm -f $(OBJDIR)/*.o

distclear: clear
	rm -f $(BINDIR)/*
