DEBUG=1

OBJDIR=./obj
BINDIR=./bin
SRCDIR=./src
INCDIR=./inc
LIBDIR=./lib

BUILD_TARGET=debug

CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -std=c99 -I $(INCDIR) -I $(LIBDIR)/*/inc -DDEBUG_AFFICHE=$(DEBUG)

.PHONY : marquage_topo tests clear distclear

marquage_topo: $(BINDIR)/$(BUILD_TARGET)/marquage_topo

$(BINDIR)/$(BUILD_TARGET)/marquage_topo: $(SRCDIR)/marquage_topo.c $(OBJDIR)/ll_adj.o $(LIBDIR)/lifo/obj/lifo.o
	$(CC) $(CFLAGS) $^ -o $@

tests: $(BINDIR)/$(BUILD_TARGET)/test_ll_adj_topo
	$(BINDIR)/$(BUILD_TARGET)/test_ll_adj_topo

$(BINDIR)/$(BUILD_TARGET)/test_ll_adj_topo: $(SRCDIR)/test_ll_adj_topo.c $(OBJDIR)/ll_adj.o $(LIBDIR)/lifo/obj/lifo.o
	$(CC) $(CFLAGS) $^ -o $@

# objets

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# autres regles

clear:
	rm -f $(OBJDIR)/*.o

distclear: clear
	rm -f $(BINDIR)/debug/*
	rm -f $(BINDIR)/release/*
