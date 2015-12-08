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
# @file searchers.py
#
# @author John DeNero and Dan Klein - UC Berkeley
# @version Regis Clouard.
#

from game import Directions
from game import Actions

import utils
import math

class SearchProblem:
    """
    This abstract class outlines the structure of a search problem.
    YOU DO NOT NEED TO CHANGE ANYTHING IN THIS CLASS, EVER.
    """

    def getStartState( self ):
        """ Returns the start state for the search problem """
        utils.raiseNotDefined()

    def getGoalState( self ):
        """ Returns the goal state for the search problem """
        utils.raiseNotDefined()

    def isGoalState( self, state ):
        """ Returns True if and only if the state is a valid goal state """
        utils.raiseNotDefined()

    def getSuccessors( self, state ):
        """ For a given state, this should return a list of triples,
        (successor, action, stepCost), where 'successor' is a
        successor to the current state, 'action' is the action
        required to get there, and 'stepCost' is the incremental
        cost of expanding to that successor """
        utils.raiseNotDefined()

    def getCostOfActions( self, actions ):
        """ This method returns the total cost of a particular sequence
        of actions.  The sequence must be composed of legal moves """
        utils.raiseNotDefined()

def tinyMazeSearch( problem ):
    """ Returns a sequence of moves that solves tinyMaze.

    For any other maze, the sequence of moves will be incorrect,
    so only use this for tinyMaze """
    return  ['South', 'South', 'West', 'South', 'West', 'West', 'South', 'West']


def nullHeuristic( state, problem ):
    return 0

def depthFirstSearch( problem ):
    """ Searches the deepest nodes in the search tree first.

    The search algorithm returns a list of actions that reaches
    the goal.
    """
    # create initial stack with one element - the path
    # starting at the given start position.
    # store pairs (coordinates, direction)
    stack = [[ (problem.getStartState(), None) ]]
    visited = [] # keep already explored positions
    while stack:
        # Get the path at the top of the stack
        current_path = stack.pop()
        # Get the last place of that path
        current_state, current_direction = current_path[-1]
        # Check if we have reached the goal
        if problem.isGoalState(current_state):
            # remove the start point and return only directions.
            return map(lambda (c, d): d, current_path[1:])
        elif current_state not in visited:
            visited += [current_state]
            # Check were we can go from here
            next_steps = problem.getSuccessors(current_state)
            # Add the new paths (one step longer) to the stack
            for c, d, w in next_steps:
                # Avoid loop!
                if not c in visited:
                    stack.append( (current_path + [ (c, d) ]) )
    return []

#######
####### Exercise 1
#######
def breadthFirstSearch( problem ):
    """ Searches the shallowest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches
    the goal.  Make sure to implement a graph search algorithm
    """

    # create initial stack with one element - the path
    # starting at the given start position.
    # store pairs (coordinates, direction)
    queue = [[ (problem.getStartState(), None) ]]
    visited = [] # keep already explored positions
    while queue:
        # Get the path at the top of the stack
        current_path = queue.pop(0)
        # Get the last place of that path
        current_state, current_direction = current_path[-1]
        # Check if we have reached the goal
        if problem.isGoalState(current_state):
            # remove the start point and return only directions.
            return map(lambda (c, d): d, current_path[1:])
        elif current_state not in visited:
            visited += [current_state]
            # Check were we can go from here
            next_steps = problem.getSuccessors(current_state)
            # Add the new paths (one step longer) to the stack
            for c, d, w in next_steps:
                # Avoid loop!
                if not c in visited:
                    queue.append( (current_path + [ (c, d) ]) )
    return []

#######
####### Exercise 2
#######
def aStarSearch( problem, heuristic = nullHeuristic ):
    """ Search the node that has the lowest combined cost and heuristic first.
    """
    fn=0
    priorityQueue = utils.PriorityQueue()
    priorityQueue.push([ (problem.getStartState(), None, 0) ], heuristic(problem.getStartState(), problem))
    visited = []
    while priorityQueue:
        current_path = priorityQueue.pop()[0]
        current_state, current_direction, current_cost = current_path[-1]
        if problem.isGoalState(current_state):
            return map(lambda (c, d, w): d, current_path[1:])
        elif current_state not in visited:
            visited += [current_state]
            next_steps = problem.getSuccessors(current_state)
            for c, d, w in next_steps:
                if not c in visited:
                    fn = current_cost - heuristic(current_state, problem) + heuristic(c, problem) + w
                    priorityQueue.push(current_path + [ (c,d,fn) ] , fn)

#######
####### Exercise 3
#######
def mazeHeuristic( state, problem ):
    """ A heuristic function estimates the cost from the given state
    to the goal.
    This heuristic is trivial.
    """

    # Positions pacman courrante
    xc = state[0]
    yc = state[1]

    # Positions finales
    xf = problem.getGoalState()[0]
    yf = problem.getGoalState()[1]

    # Distance de Manhattan
    return abs(xf-xc) + abs(yf-yc)

#######
####### Exercise 4
#######
def cornersHeuristic( state, problem ):
    """
    A heuristic for the CornersProblem that you defined.

    @param state The current search state
               (a data structure you chose in your search problem).
    @param problem The CornersProblem instance for this layout.

    """

"""    index=0
    available_distance = []

    for available in state[1]:
      if available:
        available_distance += [problem.corners[index]]
      index = index+1

    min_v = available_distance[0]

    for d in available_distance[1:]:
      min_v = min(min_v, d)

    return min_v
"""

#######
####### Exercise 5
#######
def uniformCostSearch( problem ):
    """
    Search the node of least total cost first.
    """

    # UCS <=> dijsktra <=> Astar with h(n) = 0

    fn=0
    priorityQueue = utils.PriorityQueue()
    priorityQueue.push([ (problem.getStartState(), None, 0) ], 0)
    visited = []
    while priorityQueue:
        current_path = priorityQueue.pop()[0]
        current_state, current_direction, current_cost = current_path[-1]
        if problem.isGoalState(current_state):
            return map(lambda (c, d, w): d, current_path[1:])
        elif current_state not in visited:
            visited += [current_state]
            next_steps = problem.getSuccessors(current_state)
            for c, d, w in next_steps:
                if not c in visited:
                    fn = current_cost + w
                    priorityQueue.push(current_path + [ (c,d,fn) ] , fn)


# Abbreviations
dfs = depthFirstSearch
bfs = breadthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
