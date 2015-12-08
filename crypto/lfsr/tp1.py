#!/usr/bin/python

import random

def Boolean_function(x1, x2, x3) :
    x = x3 ^ (x2 << 1) ^ (x1 << 2)
    return ((226 >> x) & 1)

def binary_string(x, n):
    s = ''
    for i in range(n) :
        if ((x >> i) & 1) == 1 : s = "1" + s
        else : s = "0" + s
    return s

def display_truth_table(f, n) :
    for i in range(1 << n) :
        print binary_string(i, n), (f >> i) & 1


def is_balanced(f, n):
    count0 = 0
    count1 = 0

    # TODO optimisation Autre solution, un seul compteur, comparer compteur est egal a 2^n-1 <=> (1 << n-1)

    for i in range (1 << n):
        if (f >> i) & 1: count1 += 1
        else: count0 += 1

    return count0 == count1

def update_LFSR(state, poly, n):
    output = state & 1
    newBit=0

    for i in range(n):
        newBit ^= ((poly >> (i+1)) & (state >> (n-i-1))) & 1

    state += (newBit << n)
    state >>= 1 # UX: ordre important (si on utilise p0)

    return output, state

def generate_keystream_with_LFSR(state, poly, n, l):
    output = 0

    for i in range(l):
        outputLFSR, state = update_LFSR(state, poly, n)
        output += outputLFSR << i

    return output

def getlfsr1():
    return 10, (1 << 10) ^ (1 << 3) ^ 1

def getlfsr2():
    return 11, (1 << 11) ^ (1 << 2) ^ 1

def getlfsr3():
    return 12, (1 << 12) ^ (1 << 6) ^ (1 << 4) ^ (1 << 1) ^ 1

def getState1(cle):
    lfsr1 = getlfsr1()

    state1 = 0
    for i in range(lfsr1[0]):
        state1 ^= ((cle >> i) & 1) << i

    return state1

def getState2(cle):
    lfsr2 = getlfsr2()

    state2 = 0

    for i in range(lfsr2[0]):
        state2 ^= ((cle >> (getlfsr1()[0] + i)) & 1) << i

    return state2

def getState3(cle):
    lfsr3 = getlfsr3()

    state3 = 0

    for i in range(lfsr3[0]):
        state3 ^= ((cle >> (getlfsr1()[0] + getlfsr2()[0] + i)) & 1) << i

    return state3

def Generator(cle, l):
    state1 = getState1(cle)
    state2 = getState2(cle)
    state3 = getState3(cle)

    output = 0

    for i in range(l):
        output1, state1 = update_LFSR(state1, getlfsr1()[1], getlfsr1()[0])
        output2, state2 = update_LFSR(state2, getlfsr2()[1], getlfsr2()[0])
        output3, state3 = update_LFSR(state3, getlfsr3()[1], getlfsr3()[0])

        output ^= Boolean_function(output1, output2, output3) << i

    return output

def statistical_test(s1, s2, l):
    standardDeviation = 1
    countNonIdenticalBits = 0

    for i in range(l):
        countNonIdenticalBits += int(((s1 >> i) & 1) != ((s2 >> i) & 1))
        #countNonIdenticalBits += (s1 & (1 << i)) != (s2 & (1 << i))

    if countNonIdenticalBits < l/3: # FIXME enonce pas clair....
        return True

    return False
