from math import isqrt

def is_prime(n):
    if n % 2 == 0:
        return n == 2
    for i in range(3, n, 2):
        if i * i > n:
            break
        if n % i == 0:
            return False
    return True

def find_highest(prime):
    ind = 0
    prim = 0
    block = prime // 30
    for p in range(prime - 2, 0, -2):
        if not is_prime(p):
            continue
        prim = p
        ind += 1
        if prim//30 != block:
            break
    print("prime {} is {} primes away: is at block {} * 30 for highest prime below prime".format(prim, ind, prim//30))

def find_lowest(prime):
    ind = 0
    prim = 0
    block = prime // 30
    for p in range(prime + 2, prime + 2**15, 2):
        if not is_prime(p):
            continue
        prim = p
        ind += 1
        if prim//30 != block:
            break
    print("prime {} is {} primes away: is at block {} * 30 for lowest prime above prime".format(prim, ind, prim//30))


def main():
    prime = int(input("please input the prime you want to find upper and lower block info for"))
    print('prime is {}, and is at block {} * 30'.format(prime, prime // 30))
    find_highest(prime)
    find_lowest(prime)
    print('if lowest is 1 away you can use this prime as an inclusive bound')
    print('if highest is 1 away you can use this prime as an exclusive bound')



main()

