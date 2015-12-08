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
# @file agents.py
#
# @author John DeNero and Dan Klein - UC Berkeley
# @version Regis Clouard.
#

from utils import manhattanDistance
from game import Directions
import random, utils

from game import Agent

def scoreEvaluationFunction( currentGameState ):
  """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
  """
  return currentGameState.getScore()

######
###### Abstract class AgentSearchAgent
######

class AgentSearchAgent( Agent ):
  """
    This abstract class provides some common elements to all of your
    agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here.
  """

  def __init__( self, evalFn = 'scoreEvaluationFunction', depth = '2' ):
    self.index = 0 # Pacman is always agent index 0
    self.evaluationFunction = utils.lookup(evalFn, globals())
    self.depth = int(depth)

  def isTerminalNode( self, gameState, depth ):
    return gameState.isLose() or gameState.isWin() or depth == 0

######
###### Exercise 1
######
class MinimaxAgent1( AgentSearchAgent ):
  """
  Minimax agent.
  """
  def getAction( self, gameState ):
    """
    Returns the minimax action from the current gameState using self.depth
    and self.evaluationFunction.
    """
    legalActions = gameState.getLegalActions(0)
    nextStates = [gameState.generateSuccessor(0, action) for action in legalActions]
    v = [self.__miniMaxValue(1, nextGameState, self.depth - 1) for nextGameState in nextStates] 
    maxV = max(v)
    listMax = []
    
    # Get the index of maxV
    for i in range(0, len(v)):
      if v[i] == maxV:
        listMax.append(i)
    # random when there is a tie
    i = random.randint(0, len(listMax) - 1)
    action = legalActions[listMax[i]]
    return action

  def __miniMaxValue( self, agentIndex, gameState, depth ):
    if self.isTerminalNode(gameState, depth): # cas d'arret
      return self.evaluationFunction(gameState)
    else: # ce n'est pas le noeud final
      prochaineActions = gameState.getLegalActions(agentIndex)
      prochainEtats = []
      for action in prochaineActions:
        prochainEtats.append(gameState.generateSuccessor(agentIndex, action))
      if agentIndex == 0: # pacman
        return self.__max_value(agentIndex, gameState, depth)
      else: # ghost
        return self.__min_value(agentIndex, gameState, depth)

  def __max_value(self, agentIndex, gameState, depth):    
    if self.isTerminalNode(gameState, depth):
      return self.evaluationFunction(gameState)
    else:
      prochaineActions = gameState.getLegalActions(agentIndex)
      v = []
      for action in prochaineActions: 
        v.append(self.__min_value(1, gameState.generateSuccessor(agentIndex, action), depth - 1))
      return max(v)

  def __min_value(self, agentIndex,  gameState, depth):    
    if self.isTerminalNode(gameState, depth):
      return self.evaluationFunction(gameState)
    else:
      prochaineActions = gameState.getLegalActions(agentIndex)
      v = []
      for action in prochaineActions:
        v.append(self.__max_value(0, gameState.generateSuccessor(agentIndex, action), depth - 1))
      return min(v)

######
###### Exercise 2
######
class MinimaxAgentN( AgentSearchAgent ):
  """
  Minimax agent with n ghosts.
  """
  def getAction( self, gameState ):
    """
    Returns the minimax action from the current gameState using self.depth
    and self.evaluationFunction.
    """
    legalActions = gameState.getLegalActions(0)
    nextStates = [gameState.generateSuccessor(0, action) for action in legalActions]
    v = [self.__miniMaxValue(1, nextGameState, self.depth - 1) for nextGameState in nextStates] 
    maxV = max(v)
    listMax = []
    
    # Get the index of maxV
    for i in range(0, len(v)):
      if v[i] == maxV:
        listMax.append(i)
    # random when there is a tie
    i = random.randint(0, len(listMax) - 1)
    action = legalActions[listMax[i]]
    return action

  def __miniMaxValue( self, agentIndex, gameState, depth ):
    if self.isTerminalNode(gameState, depth): # cas d'arret
      return self.evaluationFunction(gameState)
    else: # ce n'est pas le noeud final
      prochaineActions = gameState.getLegalActions(agentIndex)
      prochainEtats = []
      for action in prochaineActions:
        prochainEtats.append(gameState.generateSuccessor(agentIndex, action))
      if agentIndex == 0: # pacman
        return self.__max_value(agentIndex, gameState, depth)
      else: # ghost
        return self.__min_value(agentIndex, gameState, depth)

  def __max_value(self, agentIndex, gameState, depth):    
    if self.isTerminalNode(gameState, depth):
      return self.evaluationFunction(gameState)
    else:
      prochaineActions = gameState.getLegalActions(agentIndex)
      v = []
      for action in prochaineActions: 
        v.append(self.__min_value((agentIndex + 1)%gameState.getNumberOfAgents(), gameState.generateSuccessor(agentIndex, action), depth - 1))
      return max(v)

  def __min_value(self, agentIndex,  gameState, depth):    
    if self.isTerminalNode(gameState, depth):
      return self.evaluationFunction(gameState)
    else:
      prochaineActions = gameState.getLegalActions(agentIndex)
      v = []
      for action in prochaineActions:
	if agentIndex != 0:
          v.append(self.__max_value((agentIndex + 1)%gameState.getNumberOfAgents(), gameState.generateSuccessor(agentIndex, action), depth - 1))
        else:
          return max(self.__min_value(agentIndex + 1, gameState.generateSuccessor(agentIndex, action), depth - 1))
      return min(v)

######
###### Exercise 3
######
class AlphaBetaAgent(AgentSearchAgent):
  """ 
  Your minimax agent with alpha-beta pruning.
  """
  def getAction( self, gameState ):
    legalActions = gameState.getLegalActions(0)
    nextStates = [gameState.generateSuccessor(0, action) for action in legalActions]
    v = [self.__alpha_beta(1, nextGameState, self.depth - 1, -1e10, 1e10) for nextGameState in nextStates]
    maxV = max(v)
    listMax = []
    
    # Get the index of maxV
    for i in range(0, len(v)):
      if v[i] == maxV:
        listMax.append(i)
    # random when there is a tie
    i = random.randint(0, len(listMax) - 1)
    action = legalActions[listMax[i]]
    return action  

  def __alpha_beta( self, agentIndex, gameState, depth, alpha, beta):
    if self.isTerminalNode(gameState, depth):
      return self.evaluationFunction(gameState)    
    else:
      prochaineActions = gameState.getLegalActions(agentIndex)
      prochainEtats = []
      for action in prochaineActions:
        prochainEtats.append(gameState.generateSuccessor(agentIndex, action))
      if agentIndex == 0: # pacman
        return self.__max_value(agentIndex, prochainEtats, gameState, depth, alpha, beta)
      else: # ghost
        return self.__min_value(agentIndex, prochainEtats, gameState, depth, alpha, beta)

  def __max_value( self, agentIndex, prochainEtats, gameState, depth, alpha, beta):
    if self.isTerminalNode(gameState, depth):
      return self.evaluationFunction(gameState)
    else:
      v = -1e10
      for etat in prochainEtats:
        v = max(v, self.__alpha_beta((agentIndex+1)%gameState.getNumberOfAgents(), etat, depth - 1, alpha, beta))
        if v >= beta:
          return v
        alpha = max(alpha, v)
      return v

  def __min_value( self, agentIndex, prochainEtats, gameState, depth, alpha, beta):
    if self.isTerminalNode(gameState, depth):
      return self.evaluationFunction(gameState)
    else:
      v = 1e10
      for etat in prochainEtats:
        v = min(v, self.__alpha_beta((agentIndex+1)%gameState.getNumberOfAgents(), etat, depth - 1, alpha, beta))
      	if v <= alpha:
          return v
        beta = min(beta, v)
      return v
    

######
###### Exercise 4
######
class ExpectimaxAgent( AgentSearchAgent ):

  def getAction( self, gameState ):
    """
    Returns the minimax action from the current gameState using self.depth
    and self.evaluationFunction.
    """
    legalActions = gameState.getLegalActions(0)
    nextStates = [gameState.generateSuccessor(0, action) for action in legalActions]
    v = [self.__miniMaxValue(1, nextGameState, self.depth - 1) for nextGameState in nextStates] 
    maxV = max(v)
    listMax = []
    
    # Get the index of maxV
    for i in range(0, len(v)):
      if v[i] == maxV:
        listMax.append(i)
    # random when there is a tie
    i = random.randint(0, len(listMax) - 1)
    action = legalActions[listMax[i]]
    return action

  def __miniMaxValue( self, agentIndex, gameState, depth ):
    if self.isTerminalNode(gameState, depth):
      return self.evaluationFunction(gameState)    
    else:
      prochaineActions = gameState.getLegalActions(agentIndex)
      prochainEtats = []
      for action in prochaineActions:
        prochainEtats.append(gameState.generateSuccessor(agentIndex, action))
      if agentIndex == 0: # pacman
        return self.__max_value(agentIndex, prochainEtats, gameState, depth)
      else: # ghost
        return self.__min_value(agentIndex, prochainEtats, gameState, depth)

  def __max_value( self, agentIndex, prochainEtats, gameState, depth ):
    if self.isTerminalNode(gameState, depth):
      return self.evaluationFunction(gameState)
    else:
      v = []
      for etat in prochainEtats:
        v.append(self.__miniMaxValue((agentIndex+1)%gameState.getNumberOfAgents(), etat, depth - 1))
      return sum(v)/len(v)

  def __min_value( self, agentIndex, prochainEtats, gameState, depth ):
    if self.isTerminalNode(gameState, depth):
      return self.evaluationFunction(gameState)
    else:
      v = []
      for etat in prochainEtats:
        v.append(self.__miniMaxValue((agentIndex+1)%gameState.getNumberOfAgents(), etat, depth - 1))
      return sum(v)/len(v)

######
###### Exercise 5
######
def betterEvaluationFunction( currentGameState ):
  """
  Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
  evaluation function.  
  """

  " *** YOUR CODE HERE ***"
  utils.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction
