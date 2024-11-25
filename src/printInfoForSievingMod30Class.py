jumps = [1, 7, 11, 13, 17, 19, 23, 29]
diffs = [6, 4, 2, 4, 2, 4, 6, 2]
osets = [0, 6, 10, 12, 16, 18, 22, 28]
modToMask = {
    1: (255 & ~1),
    7: (255 & ~2),
    11: (255 & ~4),
    13: (255 & ~8),
    17: (255 & ~16),
    19: (255 & ~32),
    23: (255 & ~64),
    29: (255 & ~128),
}

modToOffset = {1: 0, 7: 1, 11: 2, 13: 3, 17: 4, 19: 5, 23: 6, 29: 7}


def printinfo(prime):
    cvalues = []
    avalues = []
    bvalues = []
    constvalues = [6, 4, 2, 4, 2, 4, 6, 2]
    masks = []
    i = 0
    start = 0
    for ind, jump in enumerate(jumps):
        avalues.append(start + (jump * prime) // 30)
        masks.append(modToOffset[(jump * prime) % 30])
    avalues.append(prime)
    for i in range(1, 9):
        a = avalues[i - 1] + constvalues[i - 1] * (prime // 30)
        b = avalues[i]
        bvalues.append(b - a)
    avalues.pop()
    start = prime
    for ind, jump in enumerate(jumps):
        avalues.append(start + (jump * prime) // 30)
    kprimevalue = prime // 30
    cvalue = kprimevalue
    bvalues[-1] += kprimevalue
    for i in range(len(avalues)):
        cvalues.append(cvalue)
        cvalue += kprimevalue * constvalues[i % 8] + bvalues[i % 8]

    print("prime is {}".format(prime))
    print("values generated from using b value iteraton : {}".format(cvalues))
    print("value for a in block + jump * primek + a     : {}".format(avalues))
    print("value for each mask in line above            : {}".format(masks))
    print("value for b in pos += primek * const + b     : {}".format(bvalues))
    print("value for const from previous line           : {}".format(constvalues))
    if avalues != cvalues:
        while True:
            print(prime)
            print(avalues)
            print(cvalues)


for i in range(1):
    b = 30 * i
    for p in [1, 7, 11, 13, 17, 19, 23, 29]:
        printinfo(b + p)
