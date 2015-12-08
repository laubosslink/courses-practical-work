INCDIR=./inc
SRCDIR=./src
BINDIR=./bin
OBJDIR=./obj
TESTDIR=./test
DEBUG=0

CC=g++

CFLAGS=-std=c++11 -I $(INCDIR) -DDEBUG_AFFICHE=$(DEBUG)

simulation: $(BINDIR)/simulation

tests: test_hote test_hote_home test_reseau
	./bin/test_hote
	./bin/test_hote_home
	./bin/test_reseau

test_hote: $(BINDIR)/test_hote

test_hote_home: $(BINDIR)/test_hote_home

test_reseau: $(BINDIR)/test_reseau

$(BINDIR)/simulation: $(SRCDIR)/simulation.cpp $(OBJDIR)/hote.o $(OBJDIR)/reseau.o
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR)/test_hote: $(TESTDIR)/test_hote.cpp $(OBJDIR)/hote.o
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR)/test_hote_home: $(TESTDIR)/test_hote_home.cpp $(OBJDIR)/hote.o
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR)/test_reseau: $(TESTDIR)/test_reseau.cpp $(OBJDIR)/hote.o $(OBJDIR)/reseau.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/hote.o: $(SRCDIR)/hote.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

$(OBJDIR)/reseau.o: $(SRCDIR)/reseau.cpp
	$(CC) -c $(CFLAGS) $^ -o $@
