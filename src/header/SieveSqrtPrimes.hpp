#ifndef SIEVE_SQRT_PRIMES_HPP
#define SIEVE_SQRT_PRIMES_HPP

#include "IntegralTypeIncludes.hpp"
#include "ContainerIncludes.hpp"
#include "FastMath.hpp"

// TODO test if works properly
// TODO potentially move inlcudes
// TODO maybe add prime count func for utility 
namespace SqrtPrimes {
    void blockSieveOdd(std::span<uint8_t>, uint64_t);
}

#endif
