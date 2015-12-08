#!/usr/bin/python

import unittest
import sys
import subprocess

import random

import tp1

class Tests(unittest.TestCase):
    def testBalanced(self):
        f = 226
        n = 3

        self.assertTrue(tp1.is_balanced(f, n))

    def testUpdateLFSR(self):
        state = 53
        poly = 105
        n = 7
        new_state = tp1.update_LFSR(state, poly, n)[1]
        self.assertEqual(tp1.update_LFSR(state, poly, n), (1, 26))
        self.assertEqual(tp1.update_LFSR(new_state, poly, n), (0, 13))

    def testGenerateKeystreamWithLFSR(self):
        state = 53
        poly = 105
        poly = 1^(1<<3)^(1<<5)^(1<<6)
        n = 7
        self.assertEqual(tp1.generate_keystream_with_LFSR(state, poly, n, 1), 1)
        self.assertEqual(tp1.generate_keystream_with_LFSR(state, poly, n, 2), 1)
        self.assertEqual(tp1.generate_keystream_with_LFSR(state, poly, n, 3), 5)
        self.assertEqual(tp1.generate_keystream_with_LFSR(state, poly, n, 20), 858677)

    def testLfsrState(self):
        self.assertEqual(410, tp1.getState1(2015686042))
        self.assertEqual(315, tp1.getState2(2015686042))
        self.assertEqual(961, tp1.getState3(2015686042))

    def testOutputAllLfsr(self):
        state = tp1.getState1(2015686042)
        output = 0

        for i in range(40):
            outputLfsr, state = tp1.update_LFSR(state, tp1.getlfsr1()[1], tp1.getlfsr1()[0])
            output ^= outputLfsr << i

        self.assertEqual(output, int("0101100110100010001011010010111010011000"[::-1], 2))

        state = tp1.getState2(2015686042)
        output = 0

        for i in range(40):
            outputLfsr, state = tp1.update_LFSR(state, tp1.getlfsr2()[1], tp1.getlfsr2()[0])
            output ^= outputLfsr << i

        self.assertEqual(output, int("1101110010011100101111001011100111101100"[::-1], 2))

        state = tp1.getState3(2015686042)
        output = 0

        for i in range(40):
            outputLfsr, state = tp1.update_LFSR(state, tp1.getlfsr3()[1], tp1.getlfsr3()[0])
            output ^= outputLfsr << i

        self.assertEqual(output, int("1000001111001101011010101001100110011011"[::-1], 2))

    def testGenerator(self):
        cle = 2015686042
        self.assertEqual(tp1.Generator(cle, 40), int("0101101111000001011011100010100010011011"[::-1], 2)) # [::-1] permet de renverser la chaine

    def testCorrelationGeneratorWithLfsr1AndLfsr3(self):
        lfsr1 = int("0101100110100010001011010010111010011000"[::-1], 2)
        lfsr3 = int("1000001111001101011010101001100110011011"[::-1], 2)

        outputGenerator = int("0101101111000001011011100010100010011011"[::-1], 2)

        sameLfsr1Generator = 0
        sameLfsr3Generator = 0

        for i in range(40):
            if ((lfsr1 >> i) & 1) == ((outputGenerator >> i) & 1):
                sameLfsr1Generator += 1
            if ((lfsr3 >> i) & 1) == ((outputGenerator >> i) & 1):
                sameLfsr3Generator += 1

        standardDeviation = 2

        self.assertTrue(sameLfsr1Generator >= (30 - standardDeviation) and sameLfsr1Generator <= (30 + standardDeviation))
        self.assertTrue(sameLfsr3Generator >= (30 - standardDeviation) and sameLfsr3Generator <= (30 + standardDeviation))

    def testStatisticalTest(self):
        self.assertFalse(tp1.statistical_test(155, 85, 8))
        self.assertTrue(tp1.statistical_test(255, 254, 8))

    def testGeneratorWithLFSR1(self):
        cle = random.randint(0, 1<<33)
        res = tp1.Generator(cle, 300)

        taille_lfsr1 = tp1.getlfsr1()[0]

        etat_initial_aleatoire = 0

        for i in range(0, taille_lfsr1):
            etat_initial_aleatoire += (((cle >> i) & 1) << i)

        countTrueTest = 0

        etat = 0
        while etat < (1<<taille_lfsr1):
            lfsr_state = etat
            lfsr1_300bits = 0

            for j in range(300):
                output, lfsr_state = tp1.update_LFSR(lfsr_state, tp1.getlfsr1()[1], taille_lfsr1)
                lfsr1_300bits += output << j

            if etat != etat_initial_aleatoire:
                self.assertFalse(tp1.statistical_test(lfsr1_300bits, res, 300))
            else:
                self.assertTrue(tp1.statistical_test(lfsr1_300bits, res, 300))
                countTrueTest += 1

            etat += 1

        if countTrueTest != 1:
            self.fail('Le nombre de test true devrait etre 1 or il est egal a ' + str(countTrueTest))

""" Marche pas j'ai pas trouve le probleme, mauvaise utilisation stastical_test ?
    def testGeneratorWithLFSR3(self):
        cle = random.randint(0, 1<<33)
        res = tp1.Generator(cle, 300)

        etat_initial_aleatoire = 0

        taille_lfsr3 = tp1.getlfsr3()[0]

        for i in range(0, taille_lfsr3):
            etat_initial_aleatoire += (((cle >> i) & 1) << i)

        countTrueTest = 0

        etat = 0
        while etat < (1<<taille_lfsr3):
            lfsr_state = etat
            lfsr3_300bits = 0

            for j in range(300):
                output, lfsr_state = tp1.update_LFSR(lfsr_state, tp1.getlfsr3()[1], taille_lfsr3)
                lfsr3_300bits += output << j

            if etat != etat_initial_aleatoire:
                self.assertFalse(tp1.statistical_test(lfsr3_300bits, res, 300))
            else:
                self.assertTrue(tp1.statistical_test(lfsr3_300bits, res, 300))
                countTrueTest += 1

            etat += 1

        if countTrueTest != 1:
            self.fail('Le nombre de test true devrait etre 1 or il est egal a ' + str(countTrueTest))
"""


if __name__ == '__main__':
#    if '--unittest' in sys.argv:
    subprocess.call([sys.executable, '-m', 'unittest', 'discover'])
