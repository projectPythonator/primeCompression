// for now this will have division and maybe isqrt??? 
//
//
#ifndef FAST_MATH_HPP
#define FAST_MATH_HPP
#include "IntegralTypeIncludes.hpp"
#include <cinttypes> // this might be able to be replaced
                  
// TODO does it make more sense
// TODO check if it makes more sense do the inv consts as __uint128s
namespace {
    // used for normalizing the inverse function
    constexpr uint64_t NORMALIZE_SHIFT = 68ULL;  
    constexpr uint64_t NORMALIZE_MUL = 30ULL;

    // used for fast div and mod by 30 difference of 1 to accound for rounding
    constexpr __uint128_t INVERSE_DIV_30_LITERAL = 9838263505978427528ULL; 
    constexpr __uint128_t INVERSE_MOD_30_LITERAL = 9838263505978427529ULL; 
}

uint64_t fastDivideBy30(uint64_t n) {
    return (n * INVERSE_DIV_30_LITERAL) >> NORMALIZE_SHIFT;
}

uint64_t fastModBy30(uint64_t n) {
    return n - ((n * INVERSE_MOD_30_LITERAL) >> NORMALIZE_SHIFT) * NORMALIZE_MUL;
}


bool cmpSquares(uint64_t m, uint16_t n) {
    return m <= n * n;
}

bool cmpSquares(uint64_t m, uint32_t n) {
    return m <= n * n;
}

#endif
