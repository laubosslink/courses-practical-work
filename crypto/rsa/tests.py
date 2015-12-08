#!/usr/bin/python

import unittest
import sys
import subprocess

import tp2

class Tests(unittest.TestCase):
    def testPGCD(self):
        self.assertEqual(tp2.pgcd(2,3), 1)
        self.assertEqual(tp2.pgcd(2,3), tp2.pgcd(-2, 3))

    def testBezout(self):
        ret = tp2.bezout(57, 33)
        self.assertEqual((ret[1], ret[2]), (-4, 7))

        ret = tp2.bezout(2, -4)
        self.assertEqual((ret[1], ret[2]), (-1, -1))

    def testInverse(self):
        self.assertEqual(tp2.inverse(2, 7), 4)
        self.assertEqual(tp2.inverse(-2, 7), 3)
        self.assertEqual(tp2.inverse(-9, 7), 3)

    def testTheoremeChinois(self):
        L1 = (3, 4, 5)
        L2 = (17, 11, 6)

        ret = tp2.theoreme_chinois(L1, L2)
        self.assertEqual(ret, 785)

    def testElementsInversibles(self):
        ret = tp2.elements_inversibles(60)
        self.assertEqual(ret, [1, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 49, 53, 59])

    def testRabinMiller(self):
        # https://fr.wikipedia.org/wiki/Nombre_premier#Historique_du_plus_grand_nombre_premier_connu
        self.assertTrue(tp2.rabin_miller(131071))
        self.assertTrue(tp2.rabin_miller(170141183460469231731687303715884105727))
        self.assertTrue(tp2.rabin_miller(20988936657440586486151264256610222593863921))
        self.assertFalse(tp2.rabin_miller(20988936657440586486151264256610222593863923))
        self.assertFalse(tp2.rabin_miller(20988936657440586486151264256610222593863922))
        self.assertTrue(tp2.rabin_miller(pow(2, 1279) - 1))
        self.assertFalse(tp2.rabin_miller(1022))

    def testGenerationPremier(self):
        self.assertRaises(Exception, tp2.generer_nombre_premier(10))
        self.assertTrue(tp2.rabin_miller(tp2.generer_nombre_premier(1024)))
        self.assertFalse(tp2.rabin_miller(tp2.generer_nombre_premier(1024) + 1))

    def testGenerationCleRSA(self):
        message = 11
        p, q, N, d, e = tp2.generer_cle_RSA(1024)
        c = pow(message, e, N)

        self.assertEqual(pow(c, d, N), message)

    def testSignature_RSA_CRT(self):
        message = 11

        p, q, N, d, e = tp2.generer_cle_RSA(1024)
        s1 = pow(message, d, N)

        s2 = tp2.signature_RSA_CRT(message, (p, q, N, d, e))

        self.assertEqual(s1, s2)

    def test_RSA_CRT_Bellcore(self):
        m = 11
        K = tp2.generer_cle_RSA(1024) # K[4] = e, K[2] = N

        p, q = tp2.RSA_CRT_Bellcore(m, K)

        # On peut retrouver d(decrypt)
        phi = (p - 1) * (q - 1) # On a deduit p, et q, on deduit phi pour deduire d (voir suite)
        d = tp2.inverse(K[4], phi) # d a pardir de e(encrypt) = K[4] qui est publique

        # On test si un message dechiffre avec la cle trouve est le meme que celui avec la vrai cle
        self.assertEqual(pow(m, d, (p*q)), pow(m, K[3], K[2]))

if __name__ == '__main__':
#    if '--unittest' in sys.argv:
    subprocess.call([sys.executable, '-m', 'unittest', 'discover'])
