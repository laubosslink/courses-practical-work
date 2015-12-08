INCDIR=./inc
SRCDIR=./src
BINDIR=./bin
OBJDIR=./obj

CC=g++

CFLAGS=-std=c++11 -I $(INCDIR) -DDEBUG_AFFICHE

all: vecteur set stack vecteur_capacite compteur_carac priority_queue map make_pair operateur_crochet

vecteur: $(BINDIR)/vecteur

$(BINDIR)/vecteur: $(SRCDIR)/vecteur.cpp
	$(CC) $(CFLAGS) $^ -o $@

set: $(BINDIR)/set

$(BINDIR)/set: $(SRCDIR)/set.cpp
	$(CC) $(CFLAGS) $^ -o $@

stack: $(BINDIR)/stack

$(BINDIR)/stack: $(SRCDIR)/stack.cpp
	$(CC) $(CFLAGS) $^ -o $@

vecteur_capacite: $(BINDIR)/vecteur_capacite

$(BINDIR)/vecteur_capacite: $(SRCDIR)/vecteur_capacite.cpp
	$(CC) $(CFLAGS) $^ -o $@

compteur_carac: $(BINDIR)/compteur_carac

$(BINDIR)/compteur_carac: $(SRCDIR)/compteur_carac.cpp
	$(CC) $(CFLAGS) $^ -o $@

priority_queue: $(BINDIR)/priority_queue

$(BINDIR)/priority_queue: $(SRCDIR)/priority_queue.cpp
	$(CC) $(CFLAGS) $^ -o $@

map: $(BINDIR)/map

$(BINDIR)/map: $(SRCDIR)/map.cpp
	$(CC) $(CFLAGS) $^ -o $@

make_pair: $(BINDIR)/make_pair

$(BINDIR)/make_pair: $(SRCDIR)/make_pair.cpp
	$(CC) $(CFLAGS) $^ -o $@

operateur_crochet: $(BINDIR)/operateur_crochet

$(BINDIR)/operateur_crochet: $(SRCDIR)/operateur_crochet.cpp
	$(CC) $(CFLAGS) $^ -o $@

tableau_associatif: $(BINDIR)/tableau_associatif

$(BINDIR)/tableau_associatif: $(SRCDIR)/tableau_associatif.cpp
	$(CC) $(CFLAGS) $^ -o $@

permutation_circulaire: $(BINDIR)/permutation_circulaire

$(BINDIR)/permutation_circulaire: $(SRCDIR)/permutation_circulaire.cpp
	$(CC) $(CFLAGS) $^ -o $@
