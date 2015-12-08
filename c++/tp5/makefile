INCDIR=./inc
SRCDIR=./src
TESTDIR=./test
BINDIR=./bin
OBJDIR=./obj

CC=g++

CFLAGS=-std=c++11 -I $(INCDIR) -DDEBUG_AFFICHE

all: $(BINDIR)/essai_ensemble

test: $(BINDIR)/test_ensemble

$(BINDIR)/essai_ensemble: $(SRCDIR)/essai_ensemble.cc
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR)/test_ensemble: $(TESTDIR)/test_ensemble.cc
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clear:
	rm $(OBJDIR)/*.o
