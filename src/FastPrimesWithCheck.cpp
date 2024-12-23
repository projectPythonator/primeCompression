// file used for sieving medium primes
//
#include "header/FastPrimesWithCheck.hpp"

// TODO turn into class methods
// TODO fix typing on outer loop variables
namespace SieveCompress {
    #define IS_DONE(maskIndex) \
        if (kValue >= sieveSize) [[unlikely]] \
        { \
            updatePrimeInfo(primeIndex, byteIndex, maskIndex); \
            goto next_prime; \
        }

    void crossOff_1(
            std::span<uint8_t> sieve
            std::size_t startIndex, 
            std::size_t endIndex) {

        std::size_t sieveSize = sieve.size();
        for (std::size_t primeIndex = startIndex; 
                primeIndex < endIndex; 
                primeIndex++) {
            
            std::size_t byteIndex = mid_primes_byte_mod_1[primeIndex];   // represents the current global index of this prime
            std::size_t kValue    = mid_primes_kvalue_mod_1[primeIndex]; // place holder for 30 * k + b for k
            std::size_t maskIndex = mid_primes_mask_mod_1[primeIndex];   // modified version of (byteIndex % 30) 
            std::size_t stepV1 = kValue * 6U;
            std::size_t stepV2 = kValue * 4U;
            std::size_t stepV3 = kValue * 2U;
            std::size_t stepV4 = kValue * 2U + 1U;
            switch (maskIndex) {
                default: [[unreachable]];
                for (;;) {
                    case 0: IS_DONE(0); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 1: IS_DONE(1); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 2: IS_DONE(2); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 3: IS_DONE(3); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 4: IS_DONE(4); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 5: IS_DONE(5); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 6: IS_DONE(6); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 7: IS_DONE(7); sieve[byteIndex] &= bitmask_0; byteIndex += stepV4; [[fallthrough]];
                }
            }
        }
    }

    void crossOff_7(
            std::span<uint8_t> sieve
            std::size_t startIndex, 
            std::size_t endIndex) {

        std::size_t sieveSize = sieve.size();
        for (std::size_t primeIndex = startIndex; 
                primeIndex < endIndex; 
                primeIndex++) {

            std::size_t byteIndex = mid_primes_byte_mod_1[primeIndex];   // represents the current global index of this prime
            std::size_t kValue    = mid_primes_kvalue_mod_1[primeIndex]; // place holder for 30 * k + b for k
            std::size_t maskIndex = mid_primes_mask_mod_1[primeIndex];   // modified version of (byteIndex % 30) 
            std::size_t stepV1 = kValue * 6U + 1U;
            std::size_t stepV2 = kValue * 4U + 1U;
            std::size_t stepV3 = kValue * 2U + 1U;
            std::size_t stepV4 = kValue * 4U;
            switch (maskIndex) {
                default: [[unreachable]];
                for (;;) {
                    case  8: IS_DONE( 8); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case  9: IS_DONE( 9); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 10: IS_DONE(10); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 11: IS_DONE(11); sieve[byteIndex] &= bitmask_0; byteIndex += stepV4; [[fallthrough]];
                    case 12: IS_DONE(12); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 13: IS_DONE(13); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 14: IS_DONE(14); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 15: IS_DONE(15); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                }
            }
        }
    }

    void crossOff_11(
            std::span<uint8_t> sieve
            std::size_t startIndex, 
            std::size_t endIndex) {
        
        std::size_t sieveSize = sieve.size();
        for (std::size_t primeIndex = startIndex; 
                primeIndex < endIndex; 
                primeIndex++) {

            std::size_t byteIndex = mid_primes_byte_mod_1[primeIndex];   // represents the current global index of this prime
            std::size_t kValue    = mid_primes_kvalue_mod_1[primeIndex]; // place holder for 30 * k + b for k
            std::size_t maskIndex = mid_primes_mask_mod_1[primeIndex];   // modified version of (byteIndex % 30) 

            std::size_t stepV1 = kValue * 6U + 2U;
            std::size_t stepV2 = kValue * 4U + 2U;
            std::size_t stepV3 = kValue * 2U + 0U;
            std::size_t stepV4 = kValue * 2U + 2U;
            std::size_t stepV5 = kValue * 2U + 1U;
            switch (maskIndex) {
                default: [[unreachable]];
                for (;;) {
                    case 16: IS_DONE(16); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 17: IS_DONE(17); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 18: IS_DONE(18); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 19: IS_DONE(19); sieve[byteIndex] &= bitmask_0; byteIndex += stepV4; [[fallthrough]];
                    case 20: IS_DONE(20); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 21: IS_DONE(21); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 22: IS_DONE(22); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 23: IS_DONE(23); sieve[byteIndex] &= bitmask_0; byteIndex += stepV5; [[fallthrough]];
                }
            }
        }
    }

    void crossOff_13(
            std::span<uint8_t> sieve
            std::size_t startIndex, 
            std::size_t endIndex) {

        std::size_t sieveSize = sieve.size();
        for (std::size_t primeIndex = startIndex; 
                primeIndex < endIndex; 
                primeIndex++) {

            std::size_t byteIndex = mid_primes_byte_mod_1[primeIndex];   // represents the current global index of this prime
            std::size_t kValue    = mid_primes_kvalue_mod_1[primeIndex]; // place holder for 30 * k + b for k
            std::size_t maskIndex = mid_primes_mask_mod_1[primeIndex];   // modified version of (byteIndex % 30) 

            std::size_t stepV1 = kValue * 6U + 3U;
            std::size_t stepV2 = kValue * 4U + 1U;
            std::size_t stepV3 = kValue * 2U + 1U;
            std::size_t stepV4 = kValue * 4U + 2U;
            switch (maskIndex) {
                default: [[unreachable]];
                for (;;) {
                    case 24: IS_DONE(24); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 25: IS_DONE(25); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 26: IS_DONE(26); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 27: IS_DONE(27); sieve[byteIndex] &= bitmask_0; byteIndex += stepV4; [[fallthrough]];
                    case 28: IS_DONE(28); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 29: IS_DONE(29); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 30: IS_DONE(30); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 31: IS_DONE(31); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                }
            }
        }
    }

    void crossOff_17(
            std::span<uint8_t> sieve
            std::size_t startIndex, 
            std::size_t endIndex) {

        std::size_t sieveSize = sieve.size();
        for (std::size_t primeIndex = startIndex; 
                primeIndex < endIndex; 
                primeIndex++) {
            std::size_t byteIndex = mid_primes_byte_mod_1[primeIndex];   // represents the current global index of this prime
            std::size_t kValue    = mid_primes_kvalue_mod_1[primeIndex]; // place holder for 30 * k + b for k
            std::size_t maskIndex = mid_primes_mask_mod_1[primeIndex];   // modified version of (byteIndex % 30) 

            std::size_t stepV1 = kValue * 6U + 3U;
            std::size_t stepV2 = kValue * 4U + 3U;
            std::size_t stepV4 = kValue * 4U + 2U;
            std::size_t stepV3 = kValue * 2U + 1U;
            switch (maskIndex) {
                default: [[unreachable]];
                for (;;) {
                    case 32: IS_DONE(32); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 33: IS_DONE(33); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 34: IS_DONE(34); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 35: IS_DONE(35); sieve[byteIndex] &= bitmask_0; byteIndex += stepV4; [[fallthrough]];
                    case 36: IS_DONE(36); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 37: IS_DONE(37); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 38: IS_DONE(38); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 39: IS_DONE(39); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                }
            }
        }
    }

    void crossOff_19(
            std::span<uint8_t> sieve
            std::size_t startIndex, 
            std::size_t endIndex) {

        std::size_t sieveSize = sieve.size();
        for (std::size_t primeIndex = startIndex; 
                primeIndex < endIndex; 
                primeIndex++) {
            std::size_t byteIndex = mid_primes_byte_mod_1[primeIndex];   // represents the current global index of this prime
            std::size_t kValue    = mid_primes_kvalue_mod_1[primeIndex]; // place holder for 30 * k + b for k
            std::size_t maskIndex = mid_primes_mask_mod_1[primeIndex];   // modified version of (byteIndex % 30) 

            std::size_t stepV1 = kValue * 6U + 4U;
            std::size_t stepV2 = kValue * 4U + 2U;
            std::size_t stepV3 = kValue * 2U + 2U;
            std::size_t stepV4 = kValue * 2U + 2U;
            switch (maskIndex) {
                default: [[unreachable]];
                for (;;) {
                    case 40: IS_DONE(40); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 41: IS_DONE(41); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 42: IS_DONE(42); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 43: IS_DONE(43); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 44: IS_DONE(44); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 45: IS_DONE(45); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 46: IS_DONE(46); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 47: IS_DONE(47); sieve[byteIndex] &= bitmask_0; byteIndex += stepV4; [[fallthrough]];
                }
            }
        }
    }

    void crossOff_23(
            std::span<uint8_t> sieve
            std::size_t startIndex, 
            std::size_t endIndex) {

        std::size_t sieveSize = sieve.size();
        for (std::size_t primeIndex = startIndex; 
                primeIndex < endIndex; 
                primeIndex++) {
            std::size_t byteIndex = mid_primes_byte_mod_1[primeIndex];   // represents the current global index of this prime
            std::size_t kValue    = mid_primes_kvalue_mod_1[primeIndex]; // place holder for 30 * k + b for k
            std::size_t maskIndex = mid_primes_mask_mod_1[primeIndex];   // modified version of (byteIndex % 30) 

            std::size_t stepV1 = kValue * 6U + 5U;
            std::size_t stepV2 = kValue * 4U + 3U;
            std::size_t stepV4 = kValue * 4U + 4U;
            std::size_t stepV3 = kValue * 2U + 1U;
            switch (maskIndex) {
                default: [[unreachable]];
                for (;;) {
                    case 48: IS_DONE(48); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 49: IS_DONE(49); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 50: IS_DONE(50); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 51: IS_DONE(51); sieve[byteIndex] &= bitmask_0; byteIndex += stepV4; [[fallthrough]];
                    case 52: IS_DONE(52); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 53: IS_DONE(53); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 54: IS_DONE(54); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 55: IS_DONE(55); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                }
            }
        }
    }

    void crossOff_29(
            std::span<uint8_t> sieve
            std::size_t startIndex, 
            std::size_t endIndex) {

        std::size_t sieveSize = sieve.size();
        for (std::size_t primeIndex = startIndex; 
                primeIndex < endIndex; 
                primeIndex++) {
            std::size_t byteIndex = mid_primes_byte_mod_1[primeIndex];   // represents the current global index of this prime
            std::size_t kValue    = mid_primes_kvalue_mod_1[primeIndex]; // place holder for 30 * k + b for k
            std::size_t maskIndex = mid_primes_mask_mod_1[primeIndex];   // modified version of (byteIndex % 30) 

            std::size_t stepV1 = kValue * 6U + 6U;
            std::size_t stepV2 = kValue * 4U + 4U;
            std::size_t stepV3 = kValue * 2U + 2U;
            std::size_t stepV4 = kValue * 2U + 1U;
            switch (maskIndex) {
                default: [[unreachable]];
                for (;;) {
                    case 56: IS_DONE(56); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 57: IS_DONE(57); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 58: IS_DONE(58); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 59: IS_DONE(59); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 60: IS_DONE(60); sieve[byteIndex] &= bitmask_0; byteIndex += stepV3; [[fallthrough]];
                    case 61: IS_DONE(61); sieve[byteIndex] &= bitmask_0; byteIndex += stepV2; [[fallthrough]];
                    case 62: IS_DONE(62); sieve[byteIndex] &= bitmask_0; byteIndex += stepV1; [[fallthrough]];
                    case 63: IS_DONE(63); sieve[byteIndex] &= bitmask_0; byteIndex += stepV4; [[fallthrough]];
                }
            }
        }
    }
} 

