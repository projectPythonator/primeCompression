// for now this will have division and maybe isqrt??? 
//
//
#include <cinttypes> // this might be able to be replaced
#ifndef FAST_MATH_HPP
#define FAST_MATH_HPP

namespace {
    // used for normalizing the inverse function
    constexpr uint64_t NORMALIZE_SHIFT = 68ULL;  
    constexpr uint64_t NORMALIZE_MUL = 30ULL;

    // used for fast div and mod by 30 difference of 1 to accound for rounding
    constexpr uint64_t INVERSE_DIV_30_LITERAL = 9838263505978427528ULL; 
    constexpr uint64_t INVERSE_MOD_30_LITERAL = 9838263505978427529ULL; 
}

uint64_t fastDivideBy30(uint64_t n) {
    return (__uint128_t (n) * INVERSE_DIV_30_LITERAL) >> NORMALIZE_SHIFT;
}

uint64_t fastModBy30(uint64_t n) {
    return n - ((__uint128_t (n) * INVERSE_MOD_30_LITERAL) >> NORMALIZE_SHIFT) * NORMALIZE_MUL;
}

#endif
