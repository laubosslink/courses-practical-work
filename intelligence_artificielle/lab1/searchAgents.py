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
# @file searchAgents.py
#
# @author John DeNero and Dan Klein - UC Berkeley
# @version Regis Clouard.
#

"""
This file contains all of the agents that can be selected to
control Pacman.  To select an agent, use the '-p' option
when running pacman.py.  Arguments can be passed to your agent
using '-a'.  For example, to load a SearchAgent that uses
depth first search (dfs), run the following command:

> python pacman.py -p SearchAgent -a searchFunction=depthFirstSearch

Commands to invoke other search strategies can be found in the
project description.

Please only change the parts of the file you are asked to.
Look for the lines that say

"*** YOUR CODE HERE ***"

The parts you fill in start about 3/4 of the way down.  Follow the
project description for details.

Good luck and happy searching!
"""
from game import Directions
from game import Agent
from game import Actions
import utils
import time
import searchers
import sys

class GoWestAgent( Agent ):
    "An agent that goes West until it can't."

    def getAction( self, state ):
        "The agent receives a GameState (defined in pacman.py)."
        if Directions.WEST in state.getLegalPacmanActions():
            return Directions.WEST
        else:
            return Directions.STOP

class SearchAgent( Agent ):
    """
    This very general search agent finds a path using a supplied search algorithm for a
    supplied search problem, then returns actions to follow that path.

    As a default, this agent runs DFS on a PositionSearchProblem to find location (1,1)

    Options for fn include:
      depthFirstSearch or dfs
      breadthFirstSearch or bfs


    Note: You should NOT change any code in SearchAgent
    """

    def __init__( self, fn = 'depthFirstSearch', prob = 'PositionSearchProblem', heuristic = 'nullHeuristic' ):
        # Warning: some advanced Python magic is employed below
        # to find the right functions and problems

        # Get the search function from the name and heuristic
        if fn not in dir(searchers):
            raise AttributeError, fn + ' is not a search function in searchers.py.'
        func = getattr(searchers, fn)
        if 'heuristic' not in func.func_code.co_varnames:
#            print('[SearchAgent] using function ' + fn)
            self.searchFunction = func
        else:
            if heuristic in globals().keys():
                heur = globals()[heuristic]
            elif heuristic in dir(searchers):
                heur = getattr(searchers, heuristic)
            else:
                raise AttributeError, heuristic + ' is not a function in searchAgents.py or searchers.py.'
#            print('[SearchAgent] using function %s and heuristic %s' % (fn, heuristic))
            # Note: this bit of Python trickery combines the search algorithm and the heuristic
            self.searchFunction = lambda x: func(x, heuristic=heur)

        # Get the search problem type from the name
        if prob not in globals().keys() or not prob.endswith('Problem'):
            raise AttributeError, prob + ' is not a search problem type in SearchAgents.py.'
        self.searchType = globals()[prob]
#        print('[SearchAgent] using problem type ' + prob)

    def registerInitialState( self, state ):
        """
        This is the first time that the agent sees the layout of the game board. Here, we
        choose a path to the goal.  In this phase, the agent should compute the path to the
        goal and store it in a local variable.  All of the work is done in this method!

        state: a GameState object (pacman.py)
        """
        if self.searchFunction == None: raise Exception, "No search function provided for SearchAgent"
        starttime = time.time()
        problem = self.searchType(state) # Makes a new search problem
        self.actions  = self.searchFunction(problem) # Find a path
        totalCost = problem.getCostOfActions(self.actions)
        print('Path length          : %d' % (totalCost))
        print('Time                 : %.1f s' % (time.time() - starttime))
        if '_expanded' in dir(problem):
            print('Search nodes expanded: %d' % problem._expanded)
        if not self.actions:
            sys.exit(1);

    def getAction( self, state ):
        """
        Returns the next action in the path chosen earlier (in registerInitialState).  Return
        Directions.STOP if there is no further action to take.

        state: a GameState object (pacman.py)
        """
        if 'actionIndex' not in dir(self): self.actionIndex = 0
        i = self.actionIndex
        self.actionIndex += 1
        if i < len(self.actions):
            return self.actions[i]
        else:
            return Directions.STOP

class PositionSearchProblem( searchers.SearchProblem ):
    """
    A search problem defines the state space, start state, goal test,
    successor function and cost function.  This search problem can be
    used to find paths to a particular point on the pacman board.

    The state space consists of (x,y) positions in a pacman game.

    Note: this search problem is fully specified; you should NOT change it.
    """

    def __init__( self, gameState, costFn = lambda x: 1, goal = (1,1), start = None, warn = True ):
        """
        Stores the start and goal.

        gameState: A GameState object (pacman.py)
        costFn: A function from a search state (tuple) to a non-negative number
        goal: A position in the gameState
        """
        self.walls = gameState.getWalls()
        self.__startState = gameState.getPacmanPosition()
        if start != None: self.__startState = start
        self.__goal = goal
        self.costFn = costFn
        if warn and (gameState.getNumFood() != 1 or not gameState.hasFood(*goal)):
            print 'Warning: this does not look like a regular search maze'

        # For display purposes
        self._visited, self._visitedlist, self._expanded = {}, [], 0

    def getStartState( self ):
        return self.__startState

    def getGoalState( self ):
        """ Returns the goal state (in your state space,
        not the full Pacman state space).
        """
        return self.__goal

    def isGoalState( self, state ):
        isGoal = state == self.__goal

        # For display purposes only
        if isGoal:
            self._visitedlist.append(state)
            import __main__
            if '_display' in dir(__main__):
                if 'drawExpandedCells' in dir(__main__._display): #@UndefinedVariable
                    __main__._display.drawExpandedCells(self._visitedlist) #@UndefinedVariable

        return isGoal

    def getSuccessors( self, state ):
        """
        Returns successor states, the actions they require, and a cost of 1.

         As noted in searchers.py:
             For a given state, this should return a list of triples,
         (successor, action, stepCost), where 'successor' is a
         successor to the current state, 'action' is the action
         required to get there, and 'stepCost' is the incremental
         cost of expanding to that successor
        """

        successors = []
        for action in [Directions.NORTH, Directions.SOUTH, Directions.EAST, Directions.WEST]:
            x,y = state
            dx, dy = Actions.directionToVector(action)
            nextx, nexty = int(x + dx), int(y + dy)
            if not self.walls[nextx][nexty]:
                nextState = (nextx, nexty)
                cost = self.costFn(nextState)
                successors.append( ( nextState, action, cost) )

        # Bookkeeping for display purposes
        self._expanded += 1
        if state not in self._visited:
            self._visited[state] = True
            self._visitedlist.append(state)

        return successors

    def getCostOfActions( self, actions ):
        """
        Returns the cost of a particular sequence of actions.  If those actions
        include an illegal move, return 999999
        """
        if actions == None: return 999999
        x,y= self.getStartState()
        cost = 0
        for action in actions:
            # Check figure out the next state and see whether its' legal
            dx, dy = Actions.directionToVector(action)
            x, y = int(x + dx), int(y + dy)
            if self.walls[x][y]: return 999999
            cost += self.costFn((x,y))
        return cost

class CornersProblem( searchers.SearchProblem ):
    """ This search problem finds paths through all four corners of a layout.

    You must select a suitable state space and successor function.
    """

    def __init__( self, initialState ):
        """ Stores the walls, pacman's starting position and corners.
        """
        self.walls = initialState.getWalls()
        self.startingPosition = initialState.getPacmanPosition()
        top, right = self.walls.height - 2, self.walls.width - 2
        self.corners = ((1, 1), (1, top), (right, 1), (right, top))
        for corner in self.corners:
            if not initialState.hasFood(*corner):
                print 'Warning: no food in corner ' + str(corner)
        self._expanded = 0 # Number of search nodes expanded
        self.__start = (self.startingPosition, [True, True, True, True])

    def getStartState( self ):
        """ Returns the start state (in your state space,
        not the full Pacman state space).
        """
        return self.__start

    def isGoalState( self, state ):
        """ Returns whether this search state is a goal state of the problem.
        """
        return sum(state[1]) == 0

    def getSuccessors( self, state ):
        """ Returns successor states, the actions they require, and a cost of 1.

        As noted in searchers.py:
        For a given state, this should return a list of triples,
         (successor, action, stepCost), where 'successor' is a
        successor to the current state, 'action' is the action
        required to get there, and 'stepCost' is the incremental
        cost of expanding to that successor.
        """
        successors = []
        self._expanded += 1
        for action in [Directions.NORTH, Directions.SOUTH, Directions.EAST, Directions.WEST]:
            x, y = state[0]
            nextFood = map(lambda x: x, state[1]) # Use a copy
            dx, dy = Actions.directionToVector(action)
            nextx, nexty = int(x + dx), int(y + dy)
            if not self.walls[nextx][nexty]:
                for i in range(0, 4):
                    if self.corners[i][0] == nextx and self.corners[i][1] == nexty:
                        if nextFood[i]:
                            nextFood[i] = False
                successors.append( ( ((nextx, nexty), nextFood), action, 1) )
        return successors

    def getCostOfActions( self, actions ):
        """ Returns the cost of a particular sequence of actions.

        If those actions include an illegal move, return 999999.
        This is implemented for you.
        """
        if actions == None: return 999999
        x,y = self.startingPosition
        for action in actions:
            dx, dy = Actions.directionToVector(action)
            x, y = int(x + dx), int(y + dy)
            if self.walls[x][y]: return 999999
        return len(actions)

class StayEastSearchAgent( SearchAgent ):
    """
    An agent for position search with a cost function that penalizes being in
    positions on the West side of the board.

    The cost function for stepping into a position (x,y) is 1/2^x.
    """
    def __init__( self ):
        self.searchFunction = searchers.uniformCostSearch
        costFn = lambda pos: .5 ** pos[0]
        self.searchType = lambda state: PositionSearchProblem(state, costFn)

class StayWestSearchAgent( SearchAgent ):
    """
    An agent for position search with a cost function that penalizes being in
    positions on the East side of the board.

    The cost function for stepping into a position (x,y) is 2^x.
    """
    def __init__( self ):
        self.searchFunction = searchers.uniformCostSearch
        costFn = lambda pos: 2 ** pos[0]
        self.searchType = lambda state: PositionSearchProblem(state, costFn)

class AStarCornersAgent( SearchAgent ):
    "A SearchAgent for FoodSearchProblem using A* and your foodHeuristic"
    def __init__( self ):
        self.searchFunction = lambda prob: searchers.aStarSearch(prob, searchers.cornersHeuristic)
        self.searchType = CornersProblem

