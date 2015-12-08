CC = g++
CPPFLAGS = -I ./include
CXXFLAGS = -W -Wall -ansi -pedantic -std=c++11
INC = ./include
OBJ = ./obj
SRC = ./src
BIN = ./bin

.PHONY : all clear

all : $(BIN)/main

$(BIN)/main : $(SRC)/main.cpp $(OBJ)/article.o
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

$(OBJ)/article.o : $(SRC)/article.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $^ -o $@

clear : rm -f $(OBJ)/*.o

disclear : rm -f $(BIN)/*
