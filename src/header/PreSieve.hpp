// place holder
//
//
#ifndef PRE_SIEVE_HPP
#define PRE_SIEVE_HPP

#include "PreSieveConstArrays.hpp" // pre computed sieve arrays

// TODO move methods to class??
// TODO measure cost of having applyPreSieve as a helper function vs hardcode
//  or vs highly optimized span/array decay
// TODO measure the cost of using 
namespace SieveCompress {
    void applyPreSieve(std::span<uint8_t>, std::size_t);
    void applyPreSieves(std::span<uint8_t>);
}

#endif
