#!/usr/bin/python

import unittest
import sys
import subprocess

import tp3

import random

class Tests(unittest.TestCase):
	def testVerifiePoint(self):
		self.assertTrue(tp3.verifie_point(3, 2, 5, [0,0,0]))
		self.assertTrue(tp3.verifie_point(3, 2, 5, [2,1,1]))
		self.assertFalse(tp3.verifie_point(3, 2, 5, [2,2,1]))

	def testAdditionPoints(self):
		self.assertEquals(tp3.addition_points(3, 2, 5, [2, 1, 1], [2, 4, 1])[2], 0)
		self.assertEquals(tp3.addition_points(3, 2, 5, [2, 1, 1], [2, 1, 1]), [1, 4, 1])
		self.assertEquals(tp3.addition_points(3, 2, 5, [2, 1, 1], [0, 0, 0]), [2, 1, 1])
		self.assertEquals(tp3.addition_points(3, 2, 5, [2, 1, 1], [1, 1, 1]), [2, 4, 1])
		self.assertEquals(tp3.addition_points(3, 2, 5, [2, 1, 1], [1, 4, 1]), [1, 1, 1])
		self.assertEquals(tp3.addition_points(3, 2, 5, [1, 4, 1], [1, 4, 1]), [2, 4, 1])

	def testDoubleAndAdd(self):
		self.assertEquals(tp3.double_and_add(3, 2, 5, [2,4,1], 0)[2], 0)
		self.assertEquals(tp3.double_and_add(3, 2, 5, [2,4,1], 1), [2,4,1])
		self.assertEquals(tp3.double_and_add(3, 2, 5, [2,4,1], 2), [1,1,1])
		self.assertEquals(tp3.double_and_add(3, 2, 5, [2,4,1], 3), [1,4,1])
		self.assertEquals(tp3.double_and_add(3, 2, 5, [2,4,1], 4), [2,1,1])
		self.assertEquals(tp3.double_and_add(3, 2, 5, [2,4,1], 5)[2], 0)

	def testGroupeDesPoints(self):
		self.assertEquals(len(tp3.groupe_des_points(3, 2, 5)), 5)
		self.assertEquals(len(tp3.groupe_des_points(1, 2, 11)), 16)

	def testGenerateurDuGroupe(self):
		# F5
		self.assertEquals(tp3.generateur_du_groupe(3, 2, 5)[1], [1, 5, 5, 5, 5]) # check que chaque elements est d'ordre 5 <=> chaque element est generateur du groupe

		# Aucun element genrateur du groupe dans F11 <=> pas cyclique
		orders = tp3.generateur_du_groupe(3, 2, 5)[1]
		for order in orders:
			self.assertNotEquals(order, 11)

	def testP192DiffieHellman(self):
		A, B, p, G, n = tp3.P192()

		aliceRandom = random.randint(1, n)
		bobRandom = random.randint(1, n)

		alicePoint = tp3.double_and_add(A, B, p, G, aliceRandom)
		bobPoint = tp3.double_and_add(A, B, p, G, bobRandom)

		alicePub = tp3.double_and_add(A, B, p, alicePoint, bobRandom)
		bobPub = tp3.double_and_add(A, B, p, bobPoint, aliceRandom)

		self.assertEquals(alicePub, bobPub)

	def testP192SignAndVerify(self):
		A, B, p, G, n = tp3.P192()

		k = random.randint(1, n-1)

		# cle prive alice
		a = random.randint(1, n-1)

		# cle public alice
		Apub = tp3.double_and_add(A, B, p, G, a)

		m = 11

		t, signe = tp3.signP192(k, a, m)

		self.assertTrue(tp3.verifyP192(t, signe, Apub, m))

	def testP192SignAndVerifyKFixe(self):
		A, B, p, G, n = tp3.P192()

		k = random.randint(1, n-1)

		# cle prive alice
		a = random.randint(1, n-1)

		# cle public alice
		Apub = tp3.double_and_add(A, B, p, G, a)

		m1, m2 = 11, 23

		t1, s1 = tp3.signP192(k, a, m1)
		t2, s2 = tp3.signP192(k, a, m2)

		kDeduce = (m1 - m2) * tp3.inverse(s1 - s2, n)
		tDeduce = tp3.double_and_add(A, B, p, G, k)[0]

		self.assertEquals(t1, tDeduce)

		privateKeyDeduce = (kDeduce * s1 - m1) * tp3.inverse(tDeduce, n) % n
		# <=> privateKeyDeduce = (m1*s2 - m2*s1) * tp3.inverse(tDeduce * (s1 - s2), n) % n

		self.assertEquals(a, privateKeyDeduce)


if __name__ == '__main__':
#    if '--unittest' in sys.argv:
	subprocess.call([sys.executable, '-m', 'unittest', 'discover'])