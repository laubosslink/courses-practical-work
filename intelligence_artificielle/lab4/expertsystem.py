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
# @file expertSystem.py
#
# @author Regis Clouard.
#

# This file is provided for you for testing your
# implementation. This file is also used for autograding
# your results.
# DO NOT CHANGE ANYTHING IN THIS FILE

import sys
from engine import *

def readCommand( argv ):
    """ Processes the command used to run sudoku from the command line. """
    from optparse import OptionParser
    usageStr = """
    USAGE:      python expertsystem0.py <options>
    """
    parser = OptionParser(usageStr)
    
    parser.add_option('-d', '--database', dest='database',
                      help='The database to use',
                      default='animals')
    parser.add_option('-r', '--reasoning', dest='reasoning',
                      help='The reasoning algorithm', default='forwardChaining')
    parser.add_option('-f', '--studycase', dest='studycase',
                      help='The fact base with the initial facts', default='case1')
    
    options, otherjunk = parser.parse_args(argv)

    if len(otherjunk) != 0:
        raise Exception('Command line input not understood: ' + str(otherjunk))

    args = dict()
    try:
        module = __import__(options.database)
        if options.studycase in dir(module):
            function = getattr(module, options.studycase)
        else:
            raise AttributeError, options.studycase + ' is not a valid init function.'
        args['database'] = options.database
        args['reasoning'] = options.reasoning
        args['function'] = function
    except ImportError:
        raise Exception('No file '+ options.database)
    return args

def runExpertSystem( reasoning, database, function ):
    """ The real main. """

    goalToBeProved = function()

    if reasoning == 'forwardChaining':
        print "* Initial facts:"
        initialFacts = facts[:]
        for i in range(0, len(facts)):
            print "%d) %s" % (i, facts[i])

        inferred = forwardChainingInference(facts, rules)
        print "New facts:"
        for i in range(len(inferred)):
            if inferred[i] not in facts:
                print "%d) %s" % (i, inferred[i])


    else:
        print "\n\n-----------------------------"
        print "  BACKWARD CHAINING INFERENCES"
        print "\n* Initial facts:"
        for i in range(0,len(facts)):
            print "%d) %s" % (i, facts[i])
            
        print "\nTry to prove that:", goalToBeProved
        if backwardChainingInference(goalToBeProved, facts, rules):
            print ".. PROVED"
        else:
            print ".. NOT PROVED"

if __name__ == '__main__':
    args = readCommand( sys.argv[1:] )
    print "\n-------------------------------------------------------"
    for arg in sys.argv:
        print arg,
    print "\n-------------------------------------------------------"
    runExpertSystem( **args )
