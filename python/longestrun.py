import cmath
import math
from decimal import Decimal, getcontext
from scipy import special as sp

def fair_coin_recursion(x, n):
	favorable_sequences_list = []
	for i in range(n+1):
		if i <= x:  
			favorable_sequences_list.append(2**i)
		else :
			sum = 0
			for j in range(x+1):
				sum = sum + favorable_sequences_list[i-j-1]
			favorable_sequences_list.append(sum)
	return favorable_sequences_list[-1] / 2**n

def biased_coin_recursion(x, n, p):
	q = 1 - p
	coefs = [[0] * (n+1) for _ in range(n+1)]
	for i in range(n+1):
		for j in range(i+1):
			if j <=x:
				coefs[i][j] = binomcoeff(i, j)
			else: 
				sumation = 0
				for k in range(x+1):
					sumation = sumation + coefs[i - k - 1][j - k]
				coefs[i][j] = sumation
	prob = Decimal(0)
	getcontext().prec = 20
	for i in range(len(coefs)):
		num1 = Decimal(p)**Decimal(i) * Decimal(q)**Decimal(n-i)
		prob = prob + (coefs[len(coefs)-1][i] * num1)
	return prob

def binomcoeff(n, k):
	return int(calcfactorial(n)/(calcfactorial(k) * calcfactorial(n - k)))

def calcfactorial(n):
	sumation = 1
	for i in range(n-1):
		sumation = sumation * (i+2)
	return sumation

print(fair_coin_recursion(20, 100000))
print(biased_coin_recursion(4, 2000, 0.1))
