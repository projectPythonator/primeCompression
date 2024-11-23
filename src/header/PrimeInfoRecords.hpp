#ifndef PRIME_INFO_RECORDS_HPP
#define PRIME_INFO_RECORDS_HPP

#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"
#include "SieveConstants.hpp"

namespace PrimeInfo {
    std::array<uint8_t, BoundConstants::fast_small_prime_amt> fast_primes_mask;
    std::array<uint8_t, BoundConstants::fast_small_prime_amt> fast_primes_mask_pos;
    std::array<uint16_t, BoundConstants::fast_small_prime_amt> fast_primes_kvalue;
    std::array<uint64_t, BoundConstants::fast_small_prime_amt> fast_primes_pos;

    std::vector<uint8_t> slow_primes_mask;
    std::vector<uint8_t> slow_primes_mask_pos;
    std::vector<uint32_t> slow_primes_kvalue;
    std::vector<uint32_t> slow_primes_prime_pos;
}


#endif
