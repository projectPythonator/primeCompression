def sieve(n, low, high):
    sieve = [True] * n
    rPrimes = set()
    for i in range(3, n, 2):
        if sieve[i]:
            if i > low and i <= high:
                rPrimes.add(i)
            if i > high:
                return rPrimes
            for j in range(i * i, n, 2 * i):
                sieve[j] = False
    return rPrimes


def getFreqs(primes):
    rFreqs = {1: 0, 7: 0, 11: 0, 13: 0, 17: 0, 19: 0, 23: 0, 29: 0}
    ans = 0
    for prime in primes:
        rFreqs[prime % 30] += 1
    for mod in [1, 7, 11, 13, 17, 19, 23, 29]:
        ans += rFreqs[mod]
        print("number of primes mod {} is {}".format(mod, rFreqs[mod]))
    print("total is {}".format(ans))


def main():
    print("program will generate the sizes you need for medium primes")
    low = int(input("please enter lower bound prime"))
    high = int(input("please enter upper bound prime"))
    getFreqs(sieve(2 * high, low, high))


main()
