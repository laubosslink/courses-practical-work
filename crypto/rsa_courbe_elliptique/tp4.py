#!/usr/bin/python

import copy

def multiplication_entiere(x, y):
	p = 0

	while y != 0:
		if (y & 1) == 1:
			p = p + x
		x <<= 1
		y >>= 1

	return p

def produit(n, poly, x, y):
	p = 0

	while y != 0:
		if (y & 1) > 0:
			p ^= x
		x <<= 1

		if (x & (1 << n)) > 0:
			x ^= poly

		y >>= 1

	return p


def affiche_table_multiplicative(n, poly):
	for i in xrange(1 << n):
		for j in xrange(1 << n):
			print produit(n, poly, i, j)
		print



def exp(n, poly, x, k):
	q = 1
	i = n

	# if k == 0 ?

	while i >= 0:
		q = produit(n, poly, q, q)

		if (k >> i) & 1:
			q = produit(n, poly, q, x)

		i -= 1

	return q


def inverse(n, poly, x):
	return exp(n, poly, x, pow(2, n) - 2)

def subgroup(n, poly, x):
	elmts = set()

	for i in xrange(1, pow(2, n)):
		elmts.add(exp(n, poly, x, i))

	return elmts

def generateurs(n, poly):
	elmts = []

	for i in xrange(1, pow(2, n)):
		if len(subgroup(n, poly, i)) == pow(2, n)-1:
			elmts.append(i)

	return elmts

def verifie_point(n, poly, A, B, P):
	X, Y, Z = P[0], P[1], P[2]

	if X == 0 and Y == 0 and Z == 0: # Point infini
			return True

	Y2 = produit(n, poly, Y, Y)
	XY = produit(n, poly, X, Y)
	X3 = exp(n, poly, X, 3)
	AX2 = produit(n, poly, A, produit(n,poly, X, X))

	return Y2 ^ XY == X3 ^ AX2 ^ B

def addition_points(n, poly, A, B, P, Q):
	X1, Y1, Z1 = P[0], P[1], P[2]
	X2, Y2, Z2 = Q[0], Q[1], Q[2]

	if Z1 == 0 and Z2 == Z1:
		return [0, 0, 0]

	if Z1 == 0:
		return Q

	if Z2 == 0:
		return P

	if X1 == X2 and Y1 != Y2: # P != Q
		return [0, 0, 0]

	if X1 != X2 and Y1 != Y2:
		l = produit(n, poly, (Y2 ^ Y1), inverse(n, poly, (X2 ^ X1)))
		X3 = produit(n, poly, l, l) ^ l ^ X1 ^ X2 ^ A
		Y3 = produit(n, poly, l, (X3 ^ X1)) ^ X3 ^ Y1
		return [X3, Y3, 1]

	if X1 == X2 and Y1 == Y2 and X1 == 0:
		return [0, 0, 0]

	if X1 == X2 and Y1 == Y2 and X1 != 0:
		l = X1 ^ produit(n, poly, Y1, inverse(n, poly, X1))
		X3 = produit(n, poly, l, l) ^ l ^ A
		Y3 = produit(n, poly, l, (X3 ^ X1)) ^ X3 ^ Y1
		return [X3, Y3, 1]

def double_and_add(n, poly, A, B, P, k):
	R = [0,0,0]

	if k & 1 == 1:
		R = P

	Q = P

	k >>= 1

	while k != 0:
		Q = addition_points(n, poly, A, B, Q, Q)
		if k & 1 == 1:
			R = addition_points(n, poly, A, B, R, Q)
		k >>= 1

	return R

def groupe_des_points(n, poly, A, B):
	points = []

	points.append([0,0,0]) # Point infini present par defaut, car toujours solution

	for x in xrange(pow(2,n)): # <=> 1 << n
		for y in xrange(pow(2,n)):
			if verifie_point(n, poly, A, B, [x, y, 1]):
				points.append([x,y,1])

	return points

def generateur_du_groupe(n, poly, A, B):
	points = groupe_des_points(n, poly, A, B)

	generateurs = []
	orders = []

	for i in xrange(len(points)):
		generateurs.append([])

		point = points[i]

		if point[2] == 0:
			generateurs[i].append([0, 0, 0])
			orders.append(1) # ordre 1
			continue # next point

		order = 2

		P = copy.deepcopy(point)

		while 1:
			P = addition_points(n, poly, A, B, P, point)

			if P[2] == 0:
				generateurs[i].append(P)
				orders.append(order)
				break # next point

			generateurs[i].append(P)

			order += 1

	return generateurs, orders
