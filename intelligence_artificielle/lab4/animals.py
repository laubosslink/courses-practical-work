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
# @file animals.py
#
# @author Regis Clouard.
#

from engine import addRule, addFact

print "   Load file: animals.py" 

## Add the rules
addRule(['animal_has_hair'],'animal_is_mammal')
addRule(['animal_gives_milk'], 'animal_is_mammal')
addRule(['animal_has_feathers'], 'animal_is_bird')
addRule(['animal_flies', 'animal_lays_eggs'], 'animal_is_bird')
addRule(['animal_is_mammal', 'animal_eats_meat'], 'animal_is_carnivore')
addRule(['animal_is_mammal', 'animal_has_pointed_teeth', 'animal_has_claws', 'animal_has_eyes_point_forward'], 'animal_is_carnivore')
addRule(['animal_is_mammal', 'animal_has_hoofs'], 'animal_is_ungulate')
addRule(['animal_is_mammal', 'animal_is_not_carnivore'], 'animal_is_ungulate')
addRule(['animal_is_carnivore', 'animal_has_tawny_color', 'animal_has_dark_spots'], 'animal_is_cheetah')
addRule(['animal_is_carnivore', 'animal_has_tawny_color', 'animal_has_black_stripes'], 'animal_is_tiger')
addRule(['animal_is_ungulate', 'animal_has_black_stripes'], 'animal_is_zebra')
addRule(['animal_is_ungulate', 'animal_has_long_legs', 'animal_has_long_neck', 'animal_has_tawny_color', 'animal_has_dark_spots'], 'animal_is_giraffe')
addRule(['animal_is_bird', 'animal_does_not_fly', 'animal_has_long_neck', 'animal_has_long_legs', 'animal_is_black_and_white'], 'animal_is_ostrich')
addRule(['animal_is_bird', 'animal_does_not_fly', 'animal_swims', 'animal_is_back_and_white'], 'animal_is_penguin')
addRule(['animal_is_bird', 'animal_flies'], 'animal_is_albatross')

# Consider the following study cases:

def case0():
    addFact('animal_gives_milk')
    return 'animal_gives_milk'

def case1():
    addFact('animal_gives_milk')
    addFact('animal_has_hoofs')
    addFact('animal_has_white_color')
    addFact('animal_has_black_stripes')
    return 'animal_is_zebra'

def case2():
    addFact('animal_has_feathers')
    addFact('animal_does_not_fly')
    addFact('animal_has_long_legs')
    addFact('animal_has_long_neck')
    addFact('animal_is_black_and_white')
    return 'animal_is_ostrich'

def case3():
    addFact('animal_has_hair')
    addFact('animal_eats_meat')
    addFact('animal_has_tawny_color')
    addFact('animal_has_dark_spots')
    return 'animal_is_zebra' # wrong it is a cheetah

def case4():
    addFact('animal_gives_milk')
    addFact('animal_has_hoofs')
    addFact('animal_has_long_legs')
    addFact('animal_has_long_neck')
    addFact('animal_has_tawny_color')
    addFact('animal_has_dark_spots')
    return 'animal_is_zebra' # animal_is_giraffe
