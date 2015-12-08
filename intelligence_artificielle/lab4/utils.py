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
# @file utils.py
#
# @author Regis Clouard.
#

import inspect
import sys

def raiseNotDefined():
    print "Method not implemented: %s()" % inspect.stack()[1][3]
    sys.exit(1)
