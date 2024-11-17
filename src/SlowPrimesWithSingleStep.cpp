// this file is for primes big enough to take advantage of only needing one 
// step per fwrite block

#include "/header/ByteMasks.hpp"

namespace sieveCompress {
    // only exists here right now as place holder
    // names are place holder names
    // if I change currIndex need to track what sieve we are on
    //      type will change to uint32_t if this happens or uint16_t
    void updateNumber(uint64_t primeIndex) {
        uint64_t currIndex = BIG_INDEX[primeIndex]; // might change to local index
        uint32_t kValue = BIG_K[primeIndex];
        uint8_t mValue = BIG_MOD[primeIndex];
        uint8_t mIndex = BIG_MASK_INDEX[primeIndex] & 7;
        SIEVE[currIndex] &= MASK_LOOKUP[mValue][mIndex];
        BIG_INDEX[primeIndex] += kValue * SKIP_VALUE[mIndex] + OFFSET_VALUE[mValue][mIndex];
        BIG_MASK_INDEX[primeIndex]++;


    }
}
