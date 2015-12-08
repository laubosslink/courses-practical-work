#! /usr/bin/python -*- coding: utf-8 -*-
#
# ENSICAEN
# École Nationale Supérieure d'Ingénieurs de Caen
# 6 Boulevard Maréchal Juin
# F-14050 Caen Cedex France
#
# Artificial Intelligence 2I1AE1
#

#
# @file grid.py
#
# @author Régis Clouard.
#

import math
import time

class Grid:
    """ This class stores the grid and the box size of
    a Sudoku puzzle. The grid is stored as a flat
    string of length boxsize^3. """
    computationTime = 0
    count = 0

    def __init__( self, initialGrid, solver, function = None ):
        self.__grid = initialGrid
        self.__boxSize = int(math.sqrt(math.sqrt(len(initialGrid))))
        self.__solver = solver
        self.__heuristicFunction = function

    def getRelatedCells( self, cell ):
        """ Determines which cells are in contact with the specified cell.
        Returns tuple of cells in same row, column, and box'. """
        n = self.__boxSize
        n2 = n * n
        n3 = n * n * n
        friends = set()
        row, col = cell / n2, cell % n2
        # friends of the same row
        friends.update(row * n2 + i for i in range(n2)) # grid[row][i]
        # friends of the same column
        friends.update(i * n2 + col for i in range(n2)) # grid[i][col]
        # friends of the same subgroup
        nw_corner = row / n * n3 + col / n * n
        friends.update(nw_corner + i + j for i in range(n) for j in range(0, n3, n2))
        friends.remove(cell)
        return tuple(friends)

    def getDomainValues( self ):
        """ Returns the list of all possible values for each cell. """
        possibilities = {}
        n = self.__boxSize

        for i in range(n*n*n*n):
            if self.__grid[i] == ' ':
                possibilities[i] = [str(k) for k in range(1, self.__boxSize * self.__boxSize + 1)]
            else:
                possibilities[i] = ['' + self.__grid[i]]
        return possibilities

    def getCurrentAssignment( self ):
        """ Returns the list of variable setting. """
        n = self.__boxSize
        pending_marks = []
        for i in range(n * n * n * n):
            if self.__grid[i] != ' ':
                pending_marks += [(i, '' + self.__grid[i])]
        return pending_marks

    def solve( self ):
        """ Calls the selected solver.

        Returns True or false
        """
        starttime = time.time()
        if self.__heuristicFunction:
            result = self.__solver.solve(self, self.__heuristicFunction)
        else:
            result = self.__solver.solve(self)
        self.__grid = result.values()
        self.computationTime = time.time() - starttime
        self.count = self.__solver.count
        return self.__grid

    def isValid( self ):
        for i in range(len(self.__grid)):
            for f in self.getRelatedCells(i):
                if self.__grid[i] == self.__grid[f]:
                    return False
        return True

    def display( self ):
        """ Displays grid from a string (values in row major order
        with blanks for unknowns). """
        if not self.__grid:
            print "No solution"
            return
        n = self.__boxSize
        n2 = n * n
        inset = n * " "
        fmt = '|'+('|'.join([' %s ' * n] * n)) + '|'
        sep = '+'+('+'.join(['---'  * n] * n)) + '+' 
        print inset, sep
        for i in range(n):
            for j in range(n):
                offset = (i * n + j) * n2
                cells = ""
                for x in self.__grid[offset : offset + n2]:
                    if type(x) == list:
                        x = x[0]
                    cells = cells + x
                print inset, fmt % tuple(cells)
            if i != n - 1:
                print inset, sep
        print inset, sep

    def show( self, domains ):
        n = self.__boxSize
        for y in range(n * n):
            for x in range(n * n):
                i = y * n * n + x
                print domains[i],
            print ""

    def displayPartial( self ):
        """ Displays grid from a string (values in row major order
        with blanks for unknowns). """
        if not self.__grid:
            print "No solution"
            return
        n = self.__boxSize
        n2 = n * n
        inset = n * " "
        sep = '+' + ('+'.join(['---'  * n] * n)) + '+' 
        for i in range(n):
            for j in range(n):
                offset = (i * n + j) * n2
                cells = ""
                for l in range(n):
                    for k in range(n):
                        x = self.__grid[offset+l*n+k]
                        print '{',
                        for v in  x:
                            print v,
                        print '}',
                    print ' | ',
                print inset
            print inset
        print
        print "Partial solution"
