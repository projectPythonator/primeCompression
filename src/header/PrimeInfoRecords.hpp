#ifndef PRIME_INFO_RECORDS_HPP
#define PRIME_INFO_RECORDS_HPP

#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"
#include "SieveConstants.hpp"

// TODO see if I can truly remove fast primes mask as we can likely get the mask from shifting
// TODO see if we can live with uint16_t for byte pos 
// TODO see if we can bring uint64_t on mid prime byte down to uint32_t or uint16_t
// TODO find better name than byte for the positions
// NOTE the mod of the number will be mask_pos / 8 ie mask_pos >> 3
namespace PrimeInfo {
    // std::array<uint8_t, BoundConstants::fast_small_prime_amt> fast_primes_mask;
    std::array<uint8_t , BoundConstants::fast_small_prime_amt> fast_primes_mask_pos;
    std::array<uint16_t, BoundConstants::fast_small_prime_amt> fast_primes_kvalue;
    std::array<uint16_t, BoundConstants::fast_small_prime_amt> fast_primes_pos;

    std::array<uint8_t, BoundConstants::mid_primes_mod_1_amt > mid_primes_mask_mod_1;
    std::array<uint8_t, BoundConstants::mid_primes_mod_7_amt > mid_primes_mask_mod_7;
    std::array<uint8_t, BoundConstants::mid_primes_mod_11_amt> mid_primes_mask_mod_11;
    std::array<uint8_t, BoundConstants::mid_primes_mod_13_amt> mid_primes_mask_mod_13;
    std::array<uint8_t, BoundConstants::mid_primes_mod_17_amt> mid_primes_mask_mod_17;
    std::array<uint8_t, BoundConstants::mid_primes_mod_19_amt> mid_primes_mask_mod_19;
    std::array<uint8_t, BoundConstants::mid_primes_mod_23_amt> mid_primes_mask_mod_23;
    std::array<uint8_t, BoundConstants::mid_primes_mod_29_amt> mid_primes_mask_mod_29;

    std::array<uint16_t, BoundConstants::mid_primes_mod_1_amt > mid_primes_kvalue_mod_1;
    std::array<uint16_t, BoundConstants::mid_primes_mod_7_amt > mid_primes_kvalue_mod_7;
    std::array<uint16_t, BoundConstants::mid_primes_mod_11_amt> mid_primes_kvalue_mod_11;
    std::array<uint16_t, BoundConstants::mid_primes_mod_13_amt> mid_primes_kvalue_mod_13;
    std::array<uint16_t, BoundConstants::mid_primes_mod_17_amt> mid_primes_kvalue_mod_17;
    std::array<uint16_t, BoundConstants::mid_primes_mod_19_amt> mid_primes_kvalue_mod_19;
    std::array<uint16_t, BoundConstants::mid_primes_mod_23_amt> mid_primes_kvalue_mod_23;
    std::array<uint16_t, BoundConstants::mid_primes_mod_29_amt> mid_primes_kvalue_mod_29;

    std::array<uint64_t, BoundConstants::mid_primes_mod_1_amt > mid_primes_byte_mod_1;
    std::array<uint64_t, BoundConstants::mid_primes_mod_7_amt > mid_primes_byte_mod_7;
    std::array<uint64_t, BoundConstants::mid_primes_mod_11_amt> mid_primes_byte_mod_11;
    std::array<uint64_t, BoundConstants::mid_primes_mod_13_amt> mid_primes_byte_mod_13;
    std::array<uint64_t, BoundConstants::mid_primes_mod_17_amt> mid_primes_byte_mod_17;
    std::array<uint64_t, BoundConstants::mid_primes_mod_19_amt> mid_primes_byte_mod_19;
    std::array<uint64_t, BoundConstants::mid_primes_mod_23_amt> mid_primes_byte_mod_23;
    std::array<uint64_t, BoundConstants::mid_primes_mod_29_amt> mid_primes_byte_mod_29;
    
    // std::vector<uint8_t> slow_primes_mask;
    std::vector<uint8_t> slow_primes_mask_pos;
    std::vector<uint32_t> slow_primes_kvalue;
    std::vector<uint32_t> slow_primes_prime_pos;
}


#endif
