

def startSide():
    print('#ifndef PRECOMPUTED_LOOKUP_TABLES_HPP')
    print('#define PRECOMPUTED_LOOKUP_TABLES_HPP')
    print()
    print('#include "ContainerIncludes.hpp"')
    print('#include "IntegralTypeIncludes.hpp"')
    print()
    print('// generated with PrintPresieveLookup.py in src')
    print()
    print('namespace PresieveLookup {')
    print()

def endSide():
    print()
    print('}')
    print()
    print('#endif')
    print()

def sievePrime(prime, marks, primorial):
    jumps = [6, 4, 2, 4, 2, 4, 6, 2]
    
    cur = prime 
    i = 0
    while cur < primorial:
        marks.add(cur)
        cur += (prime * jumps[i % 8])
        i += 1

def printSievePart(primes):
    mods = {1:1, 7:2, 11:4, 13:8, 17:16, 19:32, 23:64, 29:128}
    primorial = 1
    for p in primes:
        primorial *= p
    marks = set()
    for p in primes:
        sievePrime(p, marks, primorial)
    sieve = [255] * primorial
    for mark in marks:
        block = mark // 30
        mask = ~mods[mark % 30]
        sieve[block] &= mask
    strOut = '  { '
    for ind, b in enumerate(sieve):
        if ind > 0 and ind % 20 == 0:
            print(strOut)
            strOut = '    '
        strOut += "0x{:02x}".format(b)
        if ind != len(sieve)-1:
            strOut += ', '
        else:
            strOut += '}'
    return strOut

def midSide(primess):
    print('constexpr std::array<std::initializer_list<uint8_t>, 16u> presieve_lookup = {\n')
    for ind, primes in enumerate(primess):
        strOut = printSievePart(primes)
        if ind != len(primess) - 1:
            strOut += ','
        print(strOut)
    print('}};')

def main():
    primess = [
            [7,  23, 37], 
            [11, 19, 31], 
            [13, 17, 29], 
            [41, 163], 
            [43, 157], 
            [47, 151], 
            [53, 149], 
            [59, 139], 
            [61, 137], 
            [67, 131], 
            [71, 127], 
            [73, 113], 
            [79, 109], 
            [83, 107], 
            [89, 103], 
            [97, 101]] 
    startSide()
    midSide(primess)
    endSide()

main()

