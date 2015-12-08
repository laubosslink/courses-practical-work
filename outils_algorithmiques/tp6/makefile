DEBUG=1

OBJDIR=./obj
BINDIR=./bin
SRCDIR=./src
INCDIR=./inc
LIBDIR=./lib

BUILD_TARGET=debug

CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -std=c99 -I $(INCDIR) -I $(LIBDIR)/*/inc -DDEBUG_AFFICHE=$(DEBUG)

.PHONY : m_adj tests clear distclear

m_adj: $(BINDIR)/$(BUILD_TARGET)/m_adj

$(BINDIR)/$(BUILD_TARGET)/ll_adj: $(SRCDIR)/m_adj.c $(LIBDIR)/lifo/obj/lifo.o
	$(CC) $(CFLAGS) $^ -o $@

tests: $(BINDIR)/$(BUILD_TARGET)/test_m_adj
	$(BINDIR)/$(BUILD_TARGET)/test_m_adj

$(BINDIR)/$(BUILD_TARGET)/test_m_adj: $(SRCDIR)/test_m_adj.c $(OBJDIR)/m_adj.o $(LIBDIR)/lifo/obj/lifo.o
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
