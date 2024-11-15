
mods = [1, 7, 11, 13, 17, 19, 23, 29]
modsp = [7, 11, 13, 17, 19, 23, 29, 31]
bound = 2**32
span = 7 * 11 * 13 * 17 * 128
span = 2**16
spanReal = span * 30
ans = 0
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


def f(prime, ind):
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

def prime_sieve_super_fast(limit: int):
    """Optimized wheel sieve with bit compression.

    Complexity: Time: O(max(n lnln(sqrt(n)), n)),
               Space: post call O(n/ln(n)), mid-call S((n/3)/8)  4/32 == 1/8
    """
    res = [] if limit < 2 else [2] if limit == 2 else [2, 3]
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
        ind = 0
        for i in range(1, n // 3 + (limit % 6 == 1)):
            if not ((sieve[i >> 5] >> (i & 31)) & 1):
                prime = (3 * i + 1) | 1 
                f(prime, ind)
                ind += 1
                if noLoopInd:
                    break
                


getStartPoint()

print("we can free loop up till {}th prime = {}".format(sqskipInd, sqskipVersion))
print("we can check loop up till {}th prime = {}".format(noCheckInd, noCheckVersion))
print("we can no loop at {}th prime = {}".format(noLoopInd, noLoopVersion))
