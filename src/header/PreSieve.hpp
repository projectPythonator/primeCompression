#ifndef PRE_SIEVE_HPP
#define PRE_SIEVE_HPP

// need to measure how expensive it is 
#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"
#include "PresieveComputedLookupTables.hpp" // pre computed sieve arrays

// TODO measure the cost of using 
// TODO move methods to class?
// TODO measure cost of having applyPreSieve as a helper function vs hardcode
//  or vs highly optimized span/array decay
namespace PreSieve {
    void applyPreSieve(std::span<uint8_t>, std::size_t);
    void applyPreSieves(std::span<uint8_t>);
}

#endif
