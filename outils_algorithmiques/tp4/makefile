DEBUG=1

OBJDIR=./obj
BINDIR=./bin
SRCDIR=./src
INCDIR=./inc

BUILD_TARGET=debug

CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -std=c99 -I $(INCDIR) -DDEBUG_AFFICHE=$(DEBUG)

.PHONY : all genere_graphe clear distclear

all: genere_graphe l_adj

genere_graphe: $(BINDIR)/$(BUILD_TARGET)/genere_graphe

$(BINDIR)/$(BUILD_TARGET)/genere_graphe: $(SRCDIR)/genere_graphe.c
	$(CC) $^ -o $@

l_adj: $(BINDIR)/$(BUILD_TARGET)/l_adj

$(BINDIR)/$(BUILD_TARGET)/l_adj: $(SRCDIR)/l_adj.c $(OBJDIR)/$(BUILD_TARGET)/file.o
	$(CC) $(CFLAGS) $^ -o $@

# objets

$(OBJDIR)/$(BUILD_TARGET)/%.o: $(SRCDIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

# autres regles

clear: 
	rm -f $(OBJDIR)/debug/*.o
	rm -f $(OBJDIR)/release/*.o

distclear: clear
	rm -f $(BINDIR)/debug/*
	rm -f $(BINDIR)/release/*
