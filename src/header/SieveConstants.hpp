
#ifndef SIEVE_CONSTANTS_HPP
#define SIEVE_CONSTANTS_HPP
namespace SmallSieveInformation {
    constexpr std::size_t THREAD_SIEVE_SIZE = 1U << 15U; 
    constexpr std::size_t THREAD_SIEVE_MOD = THREAD_SIEVE_SIZE - 1U; 


    // this value is precomputed from the info python program
    // it covers all numbers that can take advantage of the loop
    constexpr std::size_t FAST_SMALL_PRIME_AMT = 14998U;

    // this section we are spliting up the primes into the 8 mod value 
    // these are mearly upper bounds and the actual values will be either  
    // stored here or in a sister namspace with mutable values
    // this should technically work out fine for use since we don't need to 
    // store which 8 mod value it is nor loop any switch so threads or the prog
    // can simply handle each block efficiently
    // this set might be the one that actually hads slower checks needed in the
    // loops but it should be fine
    // TODO need to math out the values for these. I might just use a py script
    constexpr std::size_t FAST_MEDIUM_MOD_1_AMT  = 0U;
    constexpr std::size_t FAST_MEDIUM_MOD_7_AMT  = 0U;
    constexpr std::size_t FAST_MEDIUM_MOD_11_AMT = 0U;
    constexpr std::size_t FAST_MEDIUM_MOD_13_AMT = 0U;
    constexpr std::size_t FAST_MEDIUM_MOD_17_AMT = 0U;
    constexpr std::size_t FAST_MEDIUM_MOD_19_AMT = 0U;
    constexpr std::size_t FAST_MEDIUM_MOD_23_AMT = 0U;
    constexpr std::size_t FAST_MEDIUM_MOD_29_AMT = 0U;
    
    // full range of the fast medium primes
    constexpr std::size_t FAST_MEDIUM_TOTAL = 40883U - FAST_SMALL_PRIME_AMT;

}
#endif