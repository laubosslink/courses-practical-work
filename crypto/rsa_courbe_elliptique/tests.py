#!/usr/bin/python

import unittest
import sys
import subprocess

import tp4

import random

class Tests(unittest.TestCase):
	def testMultiplicationEntiere(self):
		self.assertEquals(tp4.multiplication_entiere(3,4), 12)
		self.assertEquals(tp4.multiplication_entiere(3,7), 21)
		self.assertEquals(tp4.multiplication_entiere(18,7), 126)

	def testProduit(self):
		self.assertEquals(tp4.produit(3, (1<<3)^(1<<1)^1, 4, 3), 7)
		self.assertEquals(tp4.produit(3, (1<<3)^(1<<1)^1, 7, 7), 3)
		self.assertEquals(tp4.produit(8, (1<<8)^(1<<4)^(1<<3)^(1<<1)^1, 45, 72), 198)

	def testAfficheTableMultiplicative(self):
		#tp4.affiche_table_multiplicative(3, (1<<3)^(1<<1)^1)
		return

	def testExp(self):
		attendes = [(1<<1), (1<<2), (1<<1)^1, (1<<2)^(1<<1), (1<<2)^(1<<1)^1, (1<<2)^1, 1]
		for i in range(1,8):
			self.assertEquals(tp4.exp(3, (1 << 3)^(1 << 1)^1, 2, i), attendes[i-1])

	def testInverse(self):
		attendes = [1, (1<<2)^1, (1<<2)^(1<<1), (1<<2)^(1<<1)^1, (1<<2)^(1<<1)^1, (1<<2)^(1<<1), (1<<2)^1, 1]
		for i in range(1,5):
			self.assertEquals(tp4.inverse(3, (1 << 3)^(1 << 1)^1, i), attendes[i-1])

	def testSubGroup(self):
		attendes = set([(1<<1), (1<<2), (1<<1)^1, (1<<2)^(1<<1), (1<<2)^(1<<1)^1, (1<<2)^1, 1])
		self.assertEquals(tp4.subgroup(3, (1<<3)^(1<<1)^1, 2), attendes)

	def testGenerateur(self):
		self.assertEquals(len(tp4.generateurs(3, (1<<3)^(1<<1)^1)), 6) # F8
		self.assertEquals(len(tp4.generateurs(8, (1<<8)^(1<<4)^(1<<3)^(1<<1)^1)), 128) # F256

		# 2 est racine du polynome, mais n'est pas generateur => le polynome n'est pas primitif

	def testVerifiePoint(self):
		self.assertTrue(tp4.verifie_point(3, (1<<3)^(1<<1)^1, (1<<1), 1, [0,0,0]))
		self.assertTrue(tp4.verifie_point(3, (1<<3)^(1<<1)^1, (1<<1), 1, [0,1,1]))
		self.assertTrue(tp4.verifie_point(3, (1<<3)^(1<<1)^1, (1<<1), 1, [1,4,1]))
		self.assertTrue(tp4.verifie_point(3, (1<<3)^(1<<1)^1, (1<<1), 1, [1,5,1]))

	def testAdditionPoints(self):
		self.assertEquals(tp4.addition_points(3, (1<<3)^(1<<1)^1, (1<<1), 1, [0,1,1], [1,4,1]), [1,5,1])
		self.assertEquals(tp4.addition_points(3, (1<<3)^(1<<1)^1, (1<<1), 1, [1,4,1], [1,4,1]), [0,1,1])
		self.assertEquals(tp4.addition_points(3, (1<<3)^(1<<1)^1, (1<<1), 1, [1,4,1], [1,5,1])[2], 0)
		self.assertEquals(tp4.addition_points(3, (1<<3)^(1<<1)^1, (1<<1), 1, [0,1,1], [0,1,1])[2], 0)

	def testDoubleAndAdd(self):
		self.assertEquals(tp4.double_and_add(3, (1<<3)^(1<<1)^1, (1<<1), 1, [1, 4, 1], 1), [1, 4, 1])
		self.assertEquals(tp4.double_and_add(3, (1<<3)^(1<<1)^1, (1<<1), 1, [1, 4, 1], 2), [0, 1, 1])
		self.assertEquals(tp4.double_and_add(3, (1<<3)^(1<<1)^1, (1<<1), 1, [1, 4, 1], 3), [1, 5, 1])
		self.assertEquals(tp4.double_and_add(3, (1<<3)^(1<<1)^1, (1<<1), 1, [1, 4, 1], 4)[2], 0)
		self.assertEquals(tp4.double_and_add(3, (1<<3)^(1<<1)^1, (1<<1), 1, [1, 4, 1], 5), [1, 4, 1])

	def testGroupeDesPoints(self):
		self.assertEquals(tp4.groupe_des_points(3, (1<<3)^(1<<1)^1, (1<<1), 1), [[0,0,0], [0,1,1], [1,4,1], [1,5,1]])
		self.assertEquals(len(tp4.groupe_des_points(4, (1<<4)^(1<<1)^1, (1<<1), 1)), 16)
		self.assertEquals(len(tp4.groupe_des_points(4, (1<<4)^(1<<1)^1, (1<<3), 1)), 18)

	def testGenerateurDuGroupe(self):
		self.assertEquals(tp4.generateur_du_groupe(3, (1<<3)^(1<<1)^1, (1<<1), 1)[1], [1, 2, 4, 4]) # Si on retrouve deux fois l'ordre 4, on a deux generateurs
		#self.assertEquals(len(tp4.generateur_du_groupe(4, (1<<4)^(1<<1)^1, (1<<3), 1)[0]), 18)

	def testB163DH(self):
		n = 163
		poly = (1<<163)^(1<<7)^(1<<6)^(1<<3)^1
		A = 1

		B = 2982236234343851336267446656627785008148015875581
		GX = 5759917430716753942228907521556834309477856722486
		GY = 1216722771297916786238928618659324865903148082417

		G = [GX, GY, 1]

		a = random.randint(1, n)
		b = random.randint(1, n)

		bG = tp4.double_and_add(n, poly, A, B, G, b)
		aG = tp4.double_and_add(n, poly, A, B, G, a)

		abG = tp4.double_and_add(n, poly, A, B, bG, a)
		baG = tp4.double_and_add(n, poly, A, B, aG, b)

		self.assertEquals(abG, baG)

if __name__ == '__main__':
#    if '--unittest' in sys.argv:
	subprocess.call([sys.executable, '-m', 'unittest', 'discover'])
