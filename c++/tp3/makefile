CC = g++
CPPFLAGS = -I ./include
CXXFLAGS = -pedantic -std=c++11 -fno-elide-constructors
INC = ./include
OBJ = ./obj
SRC = ./src
BIN = ./bin

.PHONY : all clear

all : $(BIN)/main

$(BIN)/main : $(SRC)/main.cpp $(OBJ)/matrice.o $(OBJ)/exception.o
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

$(OBJ)/matrice.o : $(SRC)/matrice.cpp $(OBJ)/exception.o
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $^ -o $@

$(OBJ)/exception.o : $(SRC)/exception.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $^ -o $@

clear : rm -f $(OBJ)/*.o

disclear : rm -f $(BIN)/*
