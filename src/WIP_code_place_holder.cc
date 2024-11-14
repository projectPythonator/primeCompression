// fast division for inner loops will need to check if pre computing is still fsater for the smallest of not presieve primes
// the two values represent floor(2**68/30) and 68 is to normalize it again
// changed to be fast mod 30 
size_t fastmod(uint64_t n) {
    return n - ((__uint128_t (n) * 9838263505978427529ULL) >> 68) * 30;
}

