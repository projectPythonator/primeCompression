// for now this will have division and maybe isqrt??? 
//
//
#ifndef FAST_MATH_HPP
#define FAST_MATH_HPP
#include "IntegralTypeIncludes.hpp"
#include <cmath>
                  
// TODO does it make more sense
// TODO use a namespace name or does this even make sense to have it like this
namespace FastMath {
    // used for normalizing the inverse function
    constexpr uint64_t NORMALIZE_SHIFT = 68ULL;  
    constexpr uint64_t NORMALIZE_MUL = 30ULL;

    // used for fast div and mod by 30 difference of 1 to accound for rounding
    constexpr __uint128_t INVERSE_DIV_30_LITERAL = 9838263505978427528ULL; 
    constexpr __uint128_t INVERSE_MOD_30_LITERAL = 9838263505978427529ULL; 

    inline std::uint64_t fastDivideBy30(uint64_t n) {
        return (n * INVERSE_DIV_30_LITERAL) >> NORMALIZE_SHIFT;
    }

    inline std::uint64_t fastModBy30(uint64_t n) {
        return n - ((n * INVERSE_MOD_30_LITERAL) >> NORMALIZE_SHIFT) * NORMALIZE_MUL;
    }

    /*
    bool cmpSquares(std::uint64_t m, std::uint16_t n) {
        return m <= n * n;
    }

    bool cmpSquares(std::uint64_t m, std::uint32_t n) {
        return m <= n * n;
    }
    */
}

#endif
