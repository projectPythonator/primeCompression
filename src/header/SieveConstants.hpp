#ifndef SIEVE_CONSTANTS_HPP
#define SIEVE_CONSTANTS_HPP

#include "IntegralTypeIncludes.hpp"

namespace BoundConstants {
    constexpr std::size_t block_count = 8u;
    constexpr std::size_t block_size = 1U << 15U; 
    constexpr std::size_t block_mod = block_size - 1U; 


    // this value is precomputed from the info python program
    // it covers all numbers that can take advantage of the loop
    constexpr std::size_t fast_small_prime_amt = 14998U;

    // this section we are spliting up the primes into the 8 mod value 
    // these are mearly upper bounds and the actual values will be either  
    // stored here or in a sister namspace with mutable values
    // this should technically work out fine for use since we don't need to 
    // store which 8 mod value it is nor loop any switch so threads or the prog
    // can simply handle each block efficiently
    // this set might be the one that actually hads slower checks needed in the
    // loops but it should be fine
    // values generated from PrintMediumPrimeSizes.py
    constexpr std::size_t fast_medium_mod_1_amt  = 3229u;
    constexpr std::size_t fast_medium_mod_7_amt  = 3252u;
    constexpr std::size_t fast_medium_mod_11_amt = 3244u;
    constexpr std::size_t fast_medium_mod_13_amt = 3246u;
    constexpr std::size_t fast_medium_mod_17_amt = 3232u;
    constexpr std::size_t fast_medium_mod_19_amt = 3210u;
    constexpr std::size_t fast_medium_mod_23_amt = 3221u;
    constexpr std::size_t fast_medium_mod_29_amt = 3251u;
    
    // full range of the fast medium primes
    constexpr std::size_t fast_medium_total = 40883u - fast_small_prime_amt;

}
#endif
