from math import isqrt

START_INDEX = 0

fastPrimesSmallerMaxPrimeEnd = 0
fastPrimesSmallerMaxIndexEnd = 0
fastPrimesFullLoopMaxPrimeEnd = 0
fastPrimesFullLoopMaxIndexEnd = 0
slowPrimesWithLoopMaxPrimeEnd = 0
slowPrimesWithLoopMaxIndexEnd = 0


def getStartPoint(span):
    global START_INDEX
    START_INDEX = 0
    for i in range(0, 2**32, span):
        START_INDEX = i


def f(prime, ind, span):
    global fastPrimesSmallerMaxPrimeEnd, fastPrimesSmallerMaxIndexEnd
    global fastPrimesFullLoopMaxPrimeEnd, fastPrimesFullLoopMaxIndexEnd
    global slowPrimesWithLoopMaxPrimeEnd, slowPrimesWithLoopMaxIndexEnd
    mods = [1, 7, 11, 13, 17, 19, 23, 29]
    modsp = [7, 11, 13, 17, 19, 23, 29, 31]
    jumps = [(modsp[p] * prime) // 30 - (mods[p] * prime) // 30 for p in range(8)]
    maxgap = max(jumps)
    mingap = min(jumps)
    if prime**2 < START_INDEX:
        fastPrimesSmallerMaxPrimeEnd = prime
        fastPrimesSmallerMaxIndexEnd = ind
    if maxgap < span:
        fastPrimesFullLoopMaxPrimeEnd = prime
        fastPrimesFullLoopMaxIndexEnd = ind
    if mingap >= span:
        slowPrimesWithLoopMaxPrimeEnd = prime
        slowPrimesWithLoopMaxIndexEnd = ind


def block_sieve_odd(limit, span):
    """Block sieve that builds up block by block to the correct amount needed.

    Complexity: Time: O(max(n lnln(sqrt(n)), n)),
               Space: post call O(n/ln(n)), mid-call O(sqrt(n))
    """
    n, limit = limit, limit + 10
    primeIndex = 1
    end_sqrt, end_limit = isqrt(limit) + 1, (limit - 1) // 2
    sieve_and_block, smaller_primes = [True] * (end_sqrt + 1), []
    smaller_app = smaller_primes.append
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
                if slowPrimesWithLoopMaxIndexEnd:
                    return


def boundInfoForSpan(span):
    global fastPrimesSmallerMaxPrimeEnd, fastPrimesSmallerMaxIndexEnd
    global fastPrimesFullLoopMaxPrimeEnd, fastPrimesFullLoopMaxIndexEnd
    global slowPrimesWithLoopMaxPrimeEnd, slowPrimesWithLoopMaxIndexEnd
    fastPrimesSmallerMaxPrimeEnd = fastPrimesSmallerMaxIndexEnd = 0
    fastPrimesFullLoopMaxPrimeEnd = fastPrimesFullLoopMaxIndexEnd = 0
    slowPrimesWithLoopMaxPrimeEnd = slowPrimesWithLoopMaxIndexEnd = 0
    getStartPoint(span * 30)
    block_sieve_odd(1 << 30, span)

    print("\n")
    print(
        "printing data for span size of {} representing numbers [0 - {})".format(
            span, 30 * span
        )
    )
    print(
        "with given span highest start point that is below 2**32 is {} the diff between them is {}".format(
            START_INDEX, 2**32 - START_INDEX
        )
    )
    print("start point in byte index terms ie i//30 is {}".format(START_INDEX // 30))
    print("ans bigger than 2**63? {}".format(START_INDEX**2 > 2**63))
    print()
    print(
        "free loop with small primes go upto  {} th prime with value = {}".format(
            fastPrimesSmallerMaxIndexEnd, fastPrimesSmallerMaxPrimeEnd
        )
    )
    print(
        "free loop with medium primes go upto {} th prime with value = {}".format(
            fastPrimesFullLoopMaxIndexEnd, fastPrimesFullLoopMaxPrimeEnd
        )
    )
    print(
        "slower primes not full loop or optimized go till {} th prime with value = {}".format(
            slowPrimesWithLoopMaxIndexEnd, slowPrimesWithLoopMaxPrimeEnd
        )
    )
    print(
        "past this you can do single step optimization to avoid both observing primes not in the block and costly loop code when you know only a single iteratoin happends"
    )


def main():
    print()
    while (
        span := int(eval(input("please enter span you want info for or 0 to exit\n")))
    ) > 0:
        boundInfoForSpan(span)


main()
