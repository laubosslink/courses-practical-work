#! /usr/bin/python -*- coding: utf-8 -*-
#
# ENSICAEN
# École Nationale Supérieure d'Ingénieurs de Caen
# 6 Boulevard Maréchal Juin
# F-14050 Caen Cedex France
#
# Artificial Intelligence 2I1AE1
#

# @author EL HIMDI Yasmine
# @author PARMENTIER Laurent

#
# @file solvers.py
#
# @author Regis Clouard / Loic Simon
#

from grid import Grid
import random
from samples import *
import copy

class CSPSolver:
    """
    Abstract class for the solvers that implements the
    Strategy design pattern.
    YOU DO NOT NEED TO CHANGE ANYTHING IN THIS CLASS, EVER.
    """
    def __init__( self ):
        self.count = 0;
        self.clock = ['|', '/', '-', '\\']

    def displayTime( self ):
        print "\b\b\b" + self.clock[self.count % 4], 

    def solve( self, grid ):
        """ This is the method to implement for each specific solver."""
        raise Exception, "Invalid CSPSolver class, Solve() not implemented"

class CSPSolver0( CSPSolver ):
    """ Backtracking version of the solver based on simple
    uninformed backtracking search: recursive depth-first search."""

    def solve( self, grid ):
        """ Returns a solution as a dictionary of assignment
        eg: {0:'2', 1:'3', ..., 40:'5'}
        or None if no solution is found.
        @param grid a reference to the current grid."""
        domains = grid.getDomainValues()
        return self.__recursiveBacktracking(grid, domains, {})

    def __recursiveBacktracking( self, grid, domains, assignment ):
        """ This method is externalized to implement a recursive search.
        Returns the solution as list or None. """
        self.count += 1
        self.displayTime()
        if len(domains) == 0: # All cells set
            if self.isGoal(grid, assignment):
                return assignment
            return None

        variable, values =  domains.popitem()
        newAssignment = assignment.copy()
        for value in values:
            # Use a deep copy of domains to avoid backtracking issues.
            newAssignment[variable] = value
            solution = self.__recursiveBacktracking(grid, domains.copy(), newAssignment)
            if solution:
                return solution
        return None

    def isGoal( self, grid, assignment ):
        """ Tests if the assignment is a solution.
        ie. that there is not doubles in each boxes, lines and columns.
        @param assignment a dictionary with the current assignment.
        """
        for variable, value in assignment.iteritems():
            for cell in grid.getRelatedCells(variable):
                if assignment[variable] == assignment[cell]:
                    return False
        return True

#######
####### Exercise 1
#######
def defaultHeuristic( csp, assignment, grid ):
    """ Picks the first free variable."""
    for cell, p in csp.iteritems():
        if cell not in assignment:
            return cell
    
class CSPSolver1( CSPSolver ):
    def solve( self, grid, heuristicFunction = defaultHeuristic ):
        """ Foward Checking.
        Returns a solution as a dictionary of assignment, eg: {0:'2', 1:'3', ...40:'5'}
        or None if the no solution is found..
        grid is a link to the current grid.
        @param heuristicFunction is used to choose the next cell to considered.
        """
        csp = grid.getDomainValues()
        return self.__recursiveForwardChecking(grid, csp, {}, heuristicFunction)

    def __recursiveForwardChecking( self, grid, csp, assignment, heuristicFunction ):
        """ This method is externalized to implement a recursive search.
        Returns the solution as list or None. """
        self.count += 1
        self.displayTime()
        if len(csp) == len(assignment): # All cells set
            if self.isGoal(grid, assignment):
                return assignment
            return None

	cellWithoutAssignment = heuristicFunction(csp, assignment, grid)
	for cspValue in csp[cellWithoutAssignment]:
		assignment[cellWithoutAssignment] = cspValue
		csp1 = self.forwardChecking(grid, cellWithoutAssignment, cspValue, copy.deepcopy(csp))
		if csp1:
			result = self.__recursiveForwardChecking(grid, csp1, assignment, heuristicFunction)
			if result:
				return result
		del assignment[cellWithoutAssignment]
	return None

    def forwardChecking(self, grid, cellWithoutAssignment, cspValue, csp):
	for relatedCell in grid.getRelatedCells(cellWithoutAssignment):
		if cspValue in csp[relatedCell]:
			csp[relatedCell].remove(cspValue)
		if not csp[relatedCell]:
			return None
	return csp


    def isGoal( self, grid, assignment ):
        """ Tests if the assignment is a solution.
        ie. that there is not doubles in each boxes, lines and columns.
        @param assignment a dictionary with the current assignment.
        """
        for variable, value in assignment.iteritems():
            for cell in grid.getRelatedCells(variable):
                if assignment[variable] == assignment[cell]:
                    return False
        return True

#######
####### Exercise 2
#######
def myHeuristic( csp, assignment, grid ):
    """ A clever heuritic for choosing the next cell to consider.
    Returns the cell index from 0..N. """
    notAssignedCells = []

    for cell, p in csp.iteritems():
        if cell not in assignment:
            notAssignedCells += [cell]

    # Most constrained variable (variable with min remaining values)
    cellWithMinValues = notAssignedCells[0]
    for cell in notAssignedCells:
	if len(csp[cell]) < len(csp[cellWithMinValues]):
		cellWithMinValues = cell
    return cellWithMinValues

#######
####### Exercise 3
######
class CSPSolver2( CSPSolver ):
    def solve( self, grid, heuristicFunction = defaultHeuristic ):
        """ Arc Consistency as preprocessing.
        Returns the domain of values after applying
        the arc consistency technique.

        @param grid is a link to the current grid.
        @param heuristicFunction is used to choose the next cell to considered."""
	queue = []

	for cell in csp:
		for relatedCell in grid.getRelatedCells(cell):
			queue.push((cell, relatedCell,))

	while queue:
		cell, relatedCell = queue[0]
		del queue[0]
		if(self.inconsistent_value(cell, relatedCell, csp)):
			if not csp[cell]:
				return None
			for neighbors in grid.getRelatedCells(cell):
				queue.push(neighbors, cell)
	return csp

    def inconsistent_value(self, cell, relatedCell, csp):
	removed = False
	for value in csp[cell]:
		if value not in csp[relatedCell]:
			csp[relatedCell].remove(value) 
			removed = True
	return removd

    def isGoal( self, grid, assignment ):
        """ Tests if the assignment is a solution.
        ie. that there is not doubles in each boxes, lines and columns.
        @param assignment a dictionary with the current assignment.
        """
        for variable, value in assignment.iteritems():
            for cell in grid.getRelatedCells(variable):
                if assignment[variable] == assignment[cell]:
                    return False
        return True



#######
####### Exercise 4
#######
class CSPSolver3( CSPSolver ):
    def solve( self, grid, heuristicFunction = defaultHeuristic ):
        """ Forwad Checking with Arc Consistency as preprocessing.
        Returns a solution as a dictionary of assignment, eg: {0:'2', 1:'3', ...40:'5'}
        or None if the no solution is found..
        @param grid is a link to the current grid.
        @param heuristicFunction is used to choose the next cell to considered."""

        "*** YOUR CODE HERE ***"
        raise Exception, "Method not implemented: solve()"

#######
####### Exercise 5
#######
class CSPSolver4( CSPSolver ):
    def solve( self, grid, heuristicFunction = defaultHeuristic ):
        """ Maintaining Arc Consistency.
        Returns a solution as a list of assignment, eg: ['2', '3', ...'5']
        for each cell of the grid.
        @param grid is a link to the current grid.
        @param heuristicFunction is used to choose the next cell to considered."""

        "*** YOUR CODE HERE ***"
        raise Exception, "Method not implemented: solve()"
