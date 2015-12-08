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
# @file engine.py
#
# @author Regis Clouard.
#

# @author EL HIMDI Yasmine
# @author PARMENTIER Laurent

"""
This file contains the function stubs for expert system engine.
"""

import copy
from utils import raiseNotDefined

#######
####### Exercise 1
#######
# Working memory
facts = []

# Rule base
rules = []

def addFact( fact ):
    """ Adds a fact to the working memory. 

    @param fact a new fact to introduce in the working memory. """
    global facts
    if fact not in facts:
	  facts.append(fact)

def addRule( conditions, consequence ):
    """ Adds a rule in the knowledge base.

    @param conditions a condition list ['cond1',...,'cond']
    @param consequence a new fact to add to the working memory. """
    global rules
    if [conditions, consequence] not in rules:
      rules.append([conditions, consequence])

#######
####### Exercise 2
#######
def getRulePremise( rule ):
     """ Returns the premise part of the rule.
     
     @param rule a regular rule. """
     return rule[0]

def getRuleConclusion( rule ):
     """ Returns the conclusion part of the rule.
     
     @param rule a regular rule. """
     return rule[1]

#######
####### Exercise 3
#######
def isOneCondition( rule, fact ):
    """ Returns True if the fact matches one of the rule conditions.

    @param rule a rule
    @param fact a fact. """ 
    return fact in getRulePremise(rule)

#######
####### Exercise 4
#######
def forwardChainingInference( facts, rules ):
     """ The forward chaining engine.

     Keeps on firing rules until there are no rules which can be applied
     on the initial and inferred facts.
     @param facts list of current facts in the knowledge based
     @param rules list of rules in the knowledge base.
     @return the list of inferred facts. """
     counts = [len(getRulePremise(rule)) for rule in rules]
     inferred = []
     agenda = copy.deepcopy(facts)
     
     while agenda:
       p = agenda.pop() # recuperation du fait courrant
       if p not in inferred: # evite l'infinite loop A => B => ... => A
         inferred.append(p)
         for rule in rules: # parcours de l'ensemble des regles
           if isOneCondition(rule, p): # si p apparait dans une condition d'une regle
             ruleIndex = rules.index(rule)
             counts[ruleIndex] -= 1 # on a verifie une condition, donc on la "retire"
             if counts[ruleIndex] == 0: # on a vérifie l'ensemble des conditions d'une regle 
               agenda.append(getRuleConclusion(rule)) # on peut donc ajouter la consequence de cette regle
               
     return inferred

#######
####### Exercise 5
#######
def backwardChainingInference( query, facts, rules ):
     """ The backward chaining engine.
     
     @param query the fact to prove.
     @param facts list of current facts in the knowledge based
     @param rules list of rules in the knowledge base.
     @return True if the query has been proved. """
     if query in facts:
       return True

     for rule in rules:
       if query == getRuleConclusion(rule):
         Testing = True
         for fact in getRulePremise(rule):
           if not backwardChainingInference(fact, facts, rules):
             Testing = False
             break
         if Testing:
           return True
     return False
