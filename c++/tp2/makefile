CC = g++
CPPFLAGS = -I ./include
CXXFLAGS = -W -Wall -pedantic -std=c++11
INC = ./include
OBJ = ./obj
SRC = ./src
BIN = ./bin

.PHONY : all clear

all : $(BIN)/main

$(BIN)/main : $(SRC)/main.cpp $(OBJ)/complexe.o
			$(CC) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

$(OBJ)/complexe.o : $(SRC)/complexe.cpp
			$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $^ -o $@

clear : rm -f $(OBJ)/*.o

disclear : rm -f $(BIN)/*
