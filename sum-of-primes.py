import math, itertools

def isprime(n):
	""" Could be more efficient if I didn't use a fold, but F that folds are cool! """
	if n < 2 or (n % 2 == 0 and n != 2):
		return False
		
	reduce_exp = lambda x, y: False if x == False else n % y != 0
	return reduce(reduce_exp, range(3, int(math.ceil(math.sqrt(n))) + 1, 2), True)

def prime_range(x, y):
	for n in range(x, y):
		if isprime(n):
			yield n

def sum_of_primes(n):
	""" 
	Finds the prime numbers which add up to the given n (up to 5 primes),
	which, according to a recent proof (Terence Tao), is enough for any odd number.
	"""
	primes = list(prime_range(0, n + 1))
	for x in range(1, 6):
		for c in itertools.combinations_with_replacement(primes, x):
			if sum(c) == n:
				yield c
