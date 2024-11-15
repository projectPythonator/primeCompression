from math import isqrt
mods = [1, 7, 11, 13, 17, 19, 23, 29]
modsp = [7, 11, 13, 17, 19, 23, 29, 31]
bound = 2**32
span = 7 * 11 * 13 * 17 * 128
span = 2**16
spanReal = span * 30
ans = 0

THREAD_BLOCK_SPAN = 2**15
THREAD_BLOCK_RANGE = 30 * THREAD_BLOCK_SPAN

PRINT_BLOCK_SPAN = 2**18
PRINT_BLOCK_RANGE = 30 * PRINT_BLOCK_SPAN



fastPrimesSmallerMaxPrimeEnd = 0
fastPrimesSmallerMaxIndexEnd = 0
fastPrimesFullLoopMaxPrimeEnd = 0
fastPrimesFullLoopMaxIndexEnd = 0
slowPrimesWithLoopMaxPrimeEnd = 0
slowPrimesWithLoopMaxIndexEnd = 0

sqskipVersion = 0
noCheckVersion = 0
noLoopVersion = 0

sqskipInd = 0
noCheckInd = 0
noLoopInd = 0



def getStartPoint():
    global ans
    for i in range(0, 2**32, spanReal):
        ans = i
    print("start point is {}, less than uint32 {}, diff is {}".format(ans, ans < 2**32, 2**32-ans))
    print("ans bigger than 2**63? {}".format(ans**2 > 2**63))


def f(prime, ind, span):
    global sqskipVersion, sqskipInd, noCheckVersion, noCheckInd, noLoopVersion, noLoopInd
    phi = 1
    primo = 1
    jumps = [(modsp[p] * prime)//30 - (mods[p] * prime)//30 for p in range(8)]
    maxgap = max(jumps)
    mingap = min(jumps)
    if prime**2 < ans:
        sqskipVersion = prime
        sqskipInd = ind
    if maxgap < span:
        noCheckVersion = prime
        noCheckInd = ind 
    if mingap >= span:
        noLoopVersion = prime
        noLoopInd = ind
                
def block_sieve_odd(limit, span):
    """Block sieve that builds up block by block to the correct amount needed.

    Complexity: Time: O(max(n lnln(sqrt(n)), n)),
               Space: post call O(n/ln(n)), mid-call O(sqrt(n))
    """
    n, limit = limit, limit + 10
    primeIndex = 1
    end_sqrt, end_limit = isqrt(limit) + 1, (limit - 1) // 2
    sieve_and_block, primes, smaller_primes = [True] * (end_sqrt + 1), [2], []
    app, smaller_app = primes.append, smaller_primes.append
    for prime in range(3, end_sqrt, 2):
        if sieve_and_block[prime]:
            smaller_app([prime, (prime * prime - 1) // 2])
            for j in range(prime * prime, end_sqrt + 1, prime * 2):
                sieve_and_block[j] = False
    for low in range(0, end_limit, end_sqrt):
        for i in range(end_sqrt):
            sieve_and_block[i] = True
        for i, [p, idx] in enumerate(smaller_primes):
            for idx in range(idx, end_sqrt, p):
                sieve_and_block[idx] = False
            smaller_primes[i][1] = idx - end_sqrt + (0 if idx >= end_sqrt else p)
        if low == 0:
            sieve_and_block[0] = False
        for i in range(min(end_sqrt, (end_limit + 1) - low)):
            if sieve_and_block[i] and (low + i) * 2 + 1 <= n:
                f((low + i) * 2 + 1, primeIndex, span)
                primeIndex += 1
                if noLoopInd:
                    return


getStartPoint()
block_sieve_odd(1<<30)

print("we can free loop up till {}th prime = {}".format(sqskipInd, sqskipVersion))
print("we can check loop up till {}th prime = {}".format(noCheckInd, noCheckVersion))
print("we can no loop at {}th prime = {}".format(noLoopInd, noLoopVersion))
