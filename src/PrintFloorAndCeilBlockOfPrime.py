from array import array
from itertools import repeat
from math import isqrt
def prime_sieve_super_fast(limit):
    res = []
    if limit > 4:
        n = limit + 1
        flag = n % 6 == 2
        sieve = array('L', repeat(0, (n // 3 + flag >> 5) + 1))
        for i in range(1, isqrt(n) // 3 + 1):
            if not ((sieve[i >> 5] >> (i & 31)) & 1):
                k = (3 * i + 1) | 1
                for j in range(k * k // 3, n // 3 + flag, 2 * k):
                    sieve[j >> 5] |= 1 << (j & 31)
                for j in range(k * (k - 2 * (i & 1) + 4) // 3, n // 3 + flag, 2 * k):
                    sieve[j >> 5] |= 1 << (j & 31)
        res.extend([(3 * i + 1) | 1 for i in range(1, n // 3 + (limit % 6 == 1))
                   if limit-20000 < (3 * i + 1) | 1 and (not ((sieve[i >> 5] >> (i & 31)) & 1))])
    return res

def find_highest(prime, primes):
    ind = primes.index(prime)
    org = ind
    block = prime // 30
    while primes[ind]//30 == block:
        ind -= 1
    print("prime {} is {} primes away: is at block {} * 30 for highest prime below prime".format(primes[ind], org-ind, primes[ind]//30))

def find_lowest(prime, primes):
    ind = primes.index(prime)
    org = ind
    block = prime // 30
    while primes[ind]//30 == block:
        ind += 1
    print("prime {} is {} primes away: is at block {} * 30 for lowest prime above prime".format(primes[ind], ind-org, primes[ind]//30))


def main():
    prime = int(input("please input the prime you want to find upper and lower block info for"))
    primes = prime_sieve_super_fast(prime + 10000)
    print('prime is {}, and is at block {} * 30'.format(prime, prime // 30))
    find_highest(prime, primes)
    find_lowest(prime, primes)
    print('if lowest is 1 away you can use this prime as an inclusive bound')
    print('if highest is 1 away you can use this prime as an exclusive bound')



main()

