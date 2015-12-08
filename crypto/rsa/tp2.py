#!/usr/bin/python

import random
import math

def pgcd(a, b):
    a = abs(a)
    b = abs(b)

    while b != 0:
        r = a % b
        a = b
        b = r

    return a

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
        return 0

    return inverse % n

def theoreme_chinois(L1, L2):
    somme = 0
    N = L2[0] # p1

    for p in L2[1:]:
        N *= p # p2*p3*...*pi

    for i in range(len(L1)):
        pi = L2[i]

        Ni = N / pi
        xi = L1[i]
        pgcd, ui, v = bezout(Ni, pi) # <=> ui <=> inverse(ni, pi)

        somme += ui * Ni * xi

    return somme % N

def elements_inversibles(n):
    elmts = []

    for i in range(n):
        if pgcd(i, n) == 1:
            elmts.append(i)

    return elmts

def indicatrice_euler(n):
    return len(elements_inversibles(n))

def rabin_miller(p, t=10):
    # Etape 1 calculer k,q tels que p-1 = 2^(k) * q
    q = p - 1
    k = 0

    while q % 2 == 0:
        q /= 2
        k += 1

    # Etape 2 b = a^q mod p
    a = random.randint(1, p-1)
    b = pow(a, q, p)

    # Etape 3
    if b == 1 or b == p-1:
        return True

    while k > 0:
        b = (b*b) % p

        if b == (p-1):
            return True

        k -= 1

    return False

def generer_nombre_premier(n):
    if n < 8:
        raise Exception("Interdit de generer un nombre premier trop petit")

    with open("/dev/urandom", 'r') as f:
        a = (f.read(n/8)).encode('hex')

        a = int(a, 16)

        if a % 2 == 0:
            a += 1

        while not rabin_miller(a):
            a += 2

        return a

def generer_cle_RSA(n=1024):
    p = generer_nombre_premier(n)
    q = generer_nombre_premier(n)

    N = p * q
    phi = (p - 1) * (q - 1)

    e = phi

    while pgcd(e, phi) != 1:
        e = random.randint(1, phi) # TODO en realite utiliser urandom...

    d = inverse(e, phi)

    return p, q, N, d, e

def signature_RSA_CRT(m, K): # UX: Signature plus rapide que s = pow(m, e, N) grace au theoreme reste chinois
    p, q, N, d, e = K

    #public = (N, e)
    #private = (p, q, d)

    dp = d % (p-1)
    dq = d % (q-1)

    sp = pow(m, dp, p)
    sq = pow(m, dq, q)

    s = theoreme_chinois([sp, sq], [p, q])# RQ: on peut utiliser ((q^-1 mod p)qs_p + (p^-1 mod q)qs_q) mod N

    return s


def signature_RSA_CRT_faute(m, K):
    p, q, N, d, e = K

    dp = d % (p-1)
    dq = d % (q-1)

    sp = pow(m, dp, p)
    sq = pow(m, dq, q)

    # ajout d'une faute dans sq
    i = random.randint(0, int(math.log(q-1)/math.log(2)))

    if ((sq >> i) & 1) == 0:
        sq |= (1 << i)
    else:
        sq = ~sq # inverse les bits
        sq |= (1 << i)
        sq = ~sq

    s = theoreme_chinois([sp, sq], [p, q])# RQ: on peut utiliser ((q^-1 mod p)qs_p + (p^-1 mod q)qs_q) mod N

    return s

def RSA_CRT_Bellcore(m, K):
    N = K[2]

    s = signature_RSA_CRT(m, K)
    f = signature_RSA_CRT_faute(m, K)

    p = pgcd(s-f, N)
    q = N/p

    return p, q
