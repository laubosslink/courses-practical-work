DEBUG=1

OBJDIR=./obj
BINDIR=./bin
SRCDIR=./src
INCDIR=./inc

CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -std=c99 -I $(INCDIR) -DDEBUG_AFFICHE=$(DEBUG)

.PHONY : all file tests clear distclear

all : $(BINDIR)/file

$(BINDIR)/file: $(OBJDIR)/main.o $(OBJDIR)/file.o
	$(CC) $^ -o $@

# tests 

tests: $(BINDIR)/test
	$(BINDIR)/test
	
$(BINDIR)/test: $(OBJDIR)/test.o $(OBJDIR)/file.o
	$(CC) $^ -o $@
	
# objets

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

# autres regles

clear: 
	rm -f $(OBJDIR)/*.o

distclear: clear
	rm -f $(BINDIR)/*
