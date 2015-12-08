INCDIR=./inc
SRCDIR=./src
BINDIR=./bin
OBJDIR=./obj

CC=g++
CFLAGS=-std=c++11 -I $(INCDIR)

all: simulation

simulation: $(BINDIR)/simulation

$(BINDIR)/simulation: $(SRCDIR)/simulation.cpp $(OBJDIR)/Clou.o $(OBJDIR)/Compteur.o $(OBJDIR)/Lanceur.o $(OBJDIR)/Obstacle.o $(OBJDIR)/Planche.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clear:
	rm $(OBJDIR)/*.o
