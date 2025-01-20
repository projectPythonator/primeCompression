// for now this will have division and maybe isqrt??? 
//
//
#ifndef FAST_MATH_HPP
#define FAST_MATH_HPP
#include "IntegralTypeIncludes.hpp"
#include "ContainerIncludes.hpp"
#include <cmath>
                  
// TODO does it make more sense
namespace FastMath {
    // used for normalizing the inverse function
    constexpr uint64_t NORMALIZE_SHIFT = 68ULL;  
    constexpr uint64_t NORMALIZE_MUL = 30ULL;

    // used for fast div and mod by 30 difference of 1 to accound for rounding
    constexpr __uint128_t INVERSE_DIV_30_LITERAL = 9838263505978427528ULL; 
    constexpr __uint128_t INVERSE_MOD_30_LITERAL = 9838263505978427529ULL; 

    // See wikipedia for more info Division by Constant
    inline std::uint64_t fastDivideBy30(uint64_t n) {
        return (n * INVERSE_DIV_30_LITERAL) >> NORMALIZE_SHIFT;
    }

    // See wikipedia for more info Division by Constant
    inline std::uint64_t fastModBy30(uint64_t n) {
        return n - ((n * INVERSE_MOD_30_LITERAL) >> NORMALIZE_SHIFT) * NORMALIZE_MUL;
    }

    /**
     * @brief combine meta data into one hash
     * call with the parameters and get 4 checksums after program is done running
     *
     * @param param_1 a span representing 5 pieces of metaData in program topHalf, bottomHalf, firstPrime, lastPrime, numberOf0Bits
     * @param param_2 a span to hold 4 spots for creating checksums
     */
    void generate_hashes(const std::span<const std::uint64_t>, std::span<std::uint64_t>);
}

#endif
