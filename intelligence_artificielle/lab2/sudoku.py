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
# @file sudoku.py
#
# @author Régis Clouard.
#

import sys
import samples
from grid import Grid
from solvers import CSPSolver2

## code to handle timeouts
import signal
class TimeoutFunctionException(Exception):
    """Exception to raise on a timeout"""
    pass

class TimeoutFunction:

    def __init__( self, function, timeout ):
        "timeout must be at least 1 second."
        self.timeout = timeout
        self.function = function

    def handle_timeout( self, signum, frame ):
        raise TimeoutFunctionException()

    def __call__( self, *args ):
        if not 'SIGALRM' in dir(signal):
            return self.function(*args)
        old = signal.signal(signal.SIGALRM, self.handle_timeout)
        signal.alarm(self.timeout)
        try:
            result = self.function(*args)
        finally:
            signal.signal(signal.SIGALRM, old)
        signal.alarm(0)
        return result

def testHeuristic( domains ):
    return min((len(p), cell) for cell, p in enumerate(domains) if len(p)>1)[1]

def runSolvers( solver, grid, timeout, mute, correction, function=None ):
    """ The real main. """
    if function:
        grid = Grid(grid, solver, function)
    else:
#        if mute:
#            grid = Grid(grid, solver, testHeuristic)
#        else:
            grid = Grid(grid, solver)
    if not mute:
        print "Initial Sudoku:"
        grid.display()

    result = None
    timed_func = TimeoutFunction(grid.solve, timeout)
    try:
        result = timed_func()
    except TimeoutFunctionException, ex:
        print ""
        print "\nError 1: Time out:", ex

    if correction:
        if isinstance(solver, CSPSolver2):
            groundtruth = [['1'], ['2', '5', '6', '8'], ['2', '4', '6', '8'], ['4', '5', '8'], ['3', '4', '5'], ['7'], ['2', '4', '6'], ['9'], ['3', '4', '6'], ['4', '5', '7'], ['3'], ['4', '6'], ['1', '4', '5', '9'], ['2'], ['1', '5', '9'], ['1', '4', '6', '7'], ['4', '6', '7'], ['8'], ['2', '4', '7', '8'], ['2', '7', '8'], ['9'], ['6'], ['1', '3', '4'], ['1', '3', '8'], ['5'], ['2', '3', '4', '7'], ['1', '3', '4'], ['2', '4', '7', '8'], ['2', '7', '8'], ['5'], ['3'], ['1', '6', '7'], ['1', '2', '6'], ['9'], ['4', '6', '7', '8'], ['1', '4', '6'], ['4', '7', '9'], ['1'], ['3', '4'], ['5', '7', '9'], ['8'], ['5', '6', '9'], ['4', '6', '7'], ['3', '4', '5', '6', '7'], ['2'], ['6'], ['2', '7', '8', '9'], ['2', '3', '8'], ['1', '2', '5', '7', '9'], ['1', '5', '7', '9'], ['4'], ['1', '7', '8'], ['3', '5', '7', '8'], ['1', '3', '5'], ['3'], ['2', '5', '6', '8', '9'], ['2', '6', '8'], ['2', '4', '5', '7', '8', '9'], ['4', '5', '6', '7', '9'], ['2', '5', '6', '8', '9'], ['2', '4', '6', '8'], ['1'], ['4', '5', '6', '9'], ['2', '5', '8', '9'], ['4'], ['1', '2', '6', '8'], ['1', '2', '5', '8', '9'], ['1', '3', '5', '6', '9'], ['1', '2', '3', '5', '6', '8', '9'], ['2', '6', '8'], ['2', '5', '6', '8'], ['7'], ['2', '5', '8', '9'], ['2', '5', '6', '8', '9'], ['7'], ['1', '2', '4', '5', '8', '9'], ['1', '4', '5', '6', '9'], ['1', '2', '5', '6', '8', '9'], ['3'], ['2', '4', '5', '6', '8'], ['4', '5', '6', '9']]
            if result == groundtruth:
                print "EXO2: SUCCESS"
            else:
                print "EXO2: FAILURE"
            return
    if result:
        if grid.isValid():
            print "\nSudoku Solved."
            if not mute:
                grid.display()
        else:
            if not mute:
                grid.displayPartial()
    else:
        print "No solution."
    print "\nStatictics:"
    print "    - Number of explored states: %3d" % (grid.count)
    print "    - Total computation time   : %3.1fs" % (grid.computationTime)

def default( str ):
    return str + ' [Default: %default]'

def readCommand( argv ):
    """ Processes the command used to run sudoku from the command line. """
    from optparse import OptionParser
    usageStr = """
    USAGE:      python sudoku.py <options>
    EXAMPLES:   python sudoku.py --solver BacktrackingCSPSolver --grid grid2
                OR  python sudoku.py -s BacktrackingCSPSolver -g grid2
                    - solve grid 2 with the naive solver
    """
    parser = OptionParser(usageStr)
    
    parser.add_option('-s', '--solver', dest='solver',
                      help=default('the solver to use'),
                      metavar='TYPE', default='BacktrackingCSPSolver')
    parser.add_option('-g', '--grid', dest='grid',
                      help='The grid to solve', default='grid0')
    parser.add_option('-f', '--function', dest='function',
                      help='The heuristic to use', default=None)
    parser.add_option('-t', '--timeout', dest='timeout',
                      help=default('Maximum search time'), default=300)
    parser.add_option('-m', '--mute', action='store_true', dest='mute',
                      help='Display only results', default=False)
    parser.add_option('-c', '--correction', action='store_true', dest='correction',
                      help='For evalution purpose only', default=False)
    
    options, otherjunk = parser.parse_args(argv)

    if len(otherjunk) != 0:
        raise Exception('Command line input not understood: ' + str(otherjunk))
    args = dict()
    
    # Choose a Sudoku solver
    try:
        module = __import__('solvers')
        if options.solver in dir(module):
            solver = getattr(module, options.solver)
            args['solver'] = solver()
        else:
            raise Exception('Unknown solver: ' + options.solver)
    except ImportError:
        raise Exception('No file solvers.py')
    
    # Choose a grid
    try:
        module = __import__('samples')
        if options.grid in dir(module):
            args['grid'] = getattr(module, options.grid)
        else:
            raise Exception('Unknown grid: ' + options.grid)
    except ImportError:
        raise Exception('No file samples.py')

    args['timeout'] = int(options.timeout)
    args['mute'] = options.mute
    args['correction'] = options.correction

    # Choose a heuristic
    if options.function!= None:
        if options.function=="correction":
            args['function'] = testFunction
        else:
            try:
                module = __import__('solvers')
                if options.function in dir(module):
                    args['function'] = getattr(module, options.function)
                else:
                    raise Exception('Unknown heuristic: ' + options.function)
            except ImportError:
                raise Exception('No file solvers.py')
    return args

if __name__ == '__main__':
    """ The main function called when sudoku.py is run
    from the command line:

    > python sudoku.py

    See the usage string for more details.

    > python sudoku.py --help
    > python sudoku.py -h """
    args = readCommand( sys.argv[1:] ) # Get game components based on input
    print "\n-------------------------------------------------------"
    for arg in sys.argv:
        print arg,
    print "\n-------------------------------------------------------"
    runSolvers( **args )
