#!/usr/bin/python

import math

import copy

def bezout(a, b):
    u0, u1 = 1, 0
    v0, v1 = 0, 1

    while b != 0:
        q, r = a/b, a % b
        a = b * q  + r
        a, b = b, r
        u0, u1 = u1, (u0 - q * u1)
        v0, v1 = v1, (v0 - q * v1)

    if a > 0:
        return a, u0, v0

    return -a, -u0, -v0

def inverse(a, n):
    pgcd, inverse, t = bezout(a, n) # TODO unused variable t

    if pgcd != 1:
        raise Exception("Le nombre n'est pas inversible")

    return inverse % n


def verifie_point(A, B, p, P):
	X, Y, Z = P[0], P[1], P[2]

	if Z == 0: # Point infini
		return True

	return pow(Y, 2, p) == (pow(X, 3, p) + (A * X) + B) % p

def addition_points(A, B, p, P, Q):
        X1, Y1, Z1 = P[0], P[1], P[2]
        X2, Y2, Z2 = Q[0], Q[1], Q[2]

	if Z1 == 0 and Z2 == Z1:
		return [0, 0, 0]

	if Z1 == 0:
		return Q

	if Z2 == 0:
		return P

	if X1 != X2:
		l = ((Y2 - Y1) * inverse((X2 - X1) % p, p)) % p
		X3 = (pow(l, 2, p) - X1 - X2) % p
		Y3 =  (l * (X1 - X3) - Y1) % p
		return [X3, Y3, 1]
	else:
		if Y1 == 0 and Y2 == 0:
			return [X1, 0, 0]
		elif Y1 != Y2: # Cas y1 = -y2
			return [X1, 0, 0]

		# Y1 == Y2 et != 0
		l = (3 * pow(X1, 2) + A) * inverse((2 * Y1) % p, p) % p
		X3 = (pow(l, 2, p) - 2 * X1) % p
		Y3 = (l * (X1 - X3) - Y1) % p
		return [X3, Y3, 1]


def double_and_add(A, B, p, P, k):
	X, Y, Z = P[0], P[1], P[2]

	if k == 0:
		return [X, Y, 0]


	Q = [0, 0, 0]

	i = int(math.floor(math.log(k, 2))) # n

	while i >= 0:
		Q = addition_points(A, B, p, Q, Q) # Q + Q = 2Q

		if ((k >> i) & 1) == 1:
			Q = addition_points(A, B, p, Q, P) # Q = P + Q

		i -= 1

	return Q


def groupe_des_points(A, B, p):
	points = []

	points.append([0,0,0]) # Point infini present par defaut, car toujours solution

	for x in xrange(p):
		for y in xrange(p):
			if verifie_point(A, B, p, [x, y, 1]):
				points.append([x,y,1])

	return points

def generateur_du_groupe(A, B, p):
	points = groupe_des_points(A, B, p)

	groups_of_points = []
	orders = []

	for i in xrange(len(points)):
		groups_of_points.append([])

		point = points[i]

		if point[2] == 0:
			groups_of_points[i].append([0, 0, 0])
			orders.append(1) # ordre 1
			continue # next point

		order = 2

		P = copy.deepcopy(point)

		while 1:
			P = addition_points(A, B, p, P, point)

			if P[2] == 0:
				groups_of_points[i].append(P)
				orders.append(order)
				break # next point

			groups_of_points[i].append(P)

			order += 1

	return groups_of_points, orders

def P192():
	GX = int('188da80eb03090f67cbf20eb43a18800f4ff0afd82ff1012', 16)
	GY = int('07192b95ffc8da78631011ed6b24cdd573f977a11e794811', 16)
	G = [GX, GY, 1]
	B = int('64210519e59c80e70fa7e9ab72243049feb8deecc146b9b1', 16)
	n = 6277101735386680763835789423176059013767194773182842284081
	p = 6277101735386680763835789423207666416083908700390324961279
	A = -3

	return  A, B, p, G, n

def signP192(k, a, m):
	A, B, p, G, n = P192()

	K = double_and_add(A, B, p, G, k)

	t = K[0] # x of k*P

	s = (m + a*t) * inverse(k, n) % n

	return t, s

def verifyP192(t, s, Apub, m):
    A, B, p, G, n = P192()

    if (t < 1) or (t >= n) or (s < 1) or (s >= n):
        return False

    Q = addition_points(
            A,
            B,
            p,
            double_and_add(A, B, p, G, (m * inverse(s, n))),
            double_and_add(A, B, p, Apub, (t * inverse(s, n)))
        )

    if Q[0] % n == t:
        return True

    return False