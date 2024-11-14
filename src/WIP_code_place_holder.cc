// fast division for inner loops will need to check if pre computing is still fsater for the smallest of not presieve primes
// the two values represent floor(2**68/30) and 68 is to normalize it again
size_t fastdiv(uint64_t n) {
    return ((__uint128_t (n) * 9838263505978427528ULL) >> 68) % BUF_SIZE;
}

