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
# @file puzzle.py
#

# @author EL HIMDI Yasmine
# @author PARMENTIER Laurent

from engine import addRule, addFact

## Reset the memory working and the knowledge base.
print "   Load file:  puzzle.py" 

## Add the rules

# a)
addRule(['house_next_lake'], 'treasure_not_in_kitchen')

# b)
addRule(['tree_front_yard_is_oak'], 'treasure_in_garage')

# c)
addRule(['treasure_not_in_kitchen'], 'tree_front_yard_not_elm')

# e) !AvB <=> A=>B
addRule(['tree_front_yard_not_elm'], 'treasure_is_burried_under_flagpole')

# Consider the following fact:
def case():
	# d) is a fact
    addFact('house_next_lake')
    return 'None'
