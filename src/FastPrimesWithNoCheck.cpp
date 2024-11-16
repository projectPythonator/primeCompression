// not sure what includes I will need for this file
#include "rb5GlobalConstants.h"

namespace sieveCompress {


// TODO needs class extention
// TODO typing of sieve needs fixed
// in our case I am not sure if sieve size is needed 
// its here for potential portablility
// TODO check how expensive cleaning up magic numbers is
// TODO might need to switch this function up if too slow
// TODO change maskIndex typing maybe
// TODO apply correct masks
void crossOff(
        uint8_t *sieve, 
        std::size_t sieveSize, 
        std::size_t startIndex, 
        std::size_t endIndex) {
    #define IS_DONE(maskIndex) \
        if (kValue >= sieveSize) \
        { \
            updatePrimeInfo(primeIndex, byteIndex, maskIndex); \
            goto next_prime; \
        }

    
    for (std::size_t primeIndex = startIndex; primeIndex < endIndex; primeIndex++) {
        std::size_t byteIndex;   // represents the current global index of this prime
        std::size_t kValue;         // place holder for 30 * k + b for k
        std::size_t maskIndex;      // modified version of (byteIndex % 30) 
        switch (maskIndex) {
            // handles primes of form 30 * k + 1
            for (;;) {
                case 0: {
                            std::size_t maxOffset = kValue * 28U + 1U; // 
                            std::size_t unrollLimit = std::max(sieveSize, maxOffset) - maxOffset;
                            for (; byteIndex < unrollLimit; byteIndex += kValue * 30U + 1U) {
                                sieve[byteIndex + kValue *  0U + 0U] &= MASK0;
                                sieve[byteIndex + kValue *  6U + 0U] &= MASK0;
                                sieve[byteIndex + kValue * 10U + 0U] &= MASK0;
                                sieve[byteIndex + kValue * 12U + 0U] &= MASK0;
                                sieve[byteIndex + kValue * 16U + 0U] &= MASK0;
                                sieve[byteIndex + kValue * 18U + 0U] &= MASK0;
                                sieve[byteIndex + kValue * 22U + 0U] &= MASK0;
                                sieve[byteIndex + kValue * 28U + 1U] &= MASK0;
                            }
                            IS_DONE(0); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 0; [[fallthrough]];
                        }
                case 1: IS_DONE(1); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 0; [[fallthrough]];
                case 2: IS_DONE(2); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 0; [[fallthrough]];
                case 3: IS_DONE(3); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 0; [[fallthrough]];
                case 4: IS_DONE(4); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 0; [[fallthrough]];
                case 5: IS_DONE(5); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 0; [[fallthrough]];
                case 6: IS_DONE(6); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 0; [[fallthrough]];
                case 7: IS_DONE(7); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
            }

            // handles primes of form 30 * k + 7
            for (;;) {
                case  8: {
                            std::size_t maxOffset = kValue * 28U + 6U; // 
                            std::size_t unrollLimit = std::max(sieveSize, maxOffset) - maxOffset;
                            for (; byteIndex < unrollLimit; byteIndex += kValue * 30U + 7U) {
                                sieve[byteIndex + kValue *  0U + 0U] &= MASK0;
                                sieve[byteIndex + kValue *  6U + 1U] &= MASK0;
                                sieve[byteIndex + kValue * 10U + 2U] &= MASK0;
                                sieve[byteIndex + kValue * 12U + 3U] &= MASK0;
                                sieve[byteIndex + kValue * 16U + 3U] &= MASK0;
                                sieve[byteIndex + kValue * 18U + 4U] &= MASK0;
                                sieve[byteIndex + kValue * 22U + 5U] &= MASK0;
                                sieve[byteIndex + kValue * 28U + 6U] &= MASK0;
                            }
                            IS_DONE( 8); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 1; [[fallthrough]];
                         }
                case  9: IS_DONE( 9); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 1; [[fallthrough]];
                case 10: IS_DONE(10); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
                case 11: IS_DONE(11); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 0; [[fallthrough]];
                case 12: IS_DONE(12); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
                case 13: IS_DONE(13); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 1; [[fallthrough]];
                case 14: IS_DONE(14); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 1; [[fallthrough]];
                case 15: IS_DONE(15); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
            }

            // handles primes of form 30 * k + 11
            for (;;) {
                case 16: {
                            std::size_t maxOffset = kValue * 28U + 10U; // 
                            std::size_t unrollLimit = std::max(sieveSize, maxOffset) - maxOffset;
                            for (; byteIndex < unrollLimit; byteIndex += kValue * 30U + 11U) {
                                sieve[byteIndex + kValue *  0U +  0U] &= MASK0;
                                sieve[byteIndex + kValue *  6U +  2U] &= MASK0;
                                sieve[byteIndex + kValue * 10U +  4U] &= MASK0;
                                sieve[byteIndex + kValue * 12U +  4U] &= MASK0;
                                sieve[byteIndex + kValue * 16U +  6U] &= MASK0;
                                sieve[byteIndex + kValue * 18U +  6U] &= MASK0;
                                sieve[byteIndex + kValue * 22U +  8U] &= MASK0;
                                sieve[byteIndex + kValue * 28U + 10U] &= MASK0;
                            }
                            IS_DONE(16); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 2; [[fallthrough]];
                        }
                case 17: IS_DONE(17); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 2; [[fallthrough]];
                case 18: IS_DONE(18); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 0; [[fallthrough]];
                case 19: IS_DONE(19); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 2; [[fallthrough]];
                case 20: IS_DONE(20); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 0; [[fallthrough]];
                case 21: IS_DONE(21); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 2; [[fallthrough]];
                case 22: IS_DONE(22); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 2; [[fallthrough]];
                case 23: IS_DONE(23); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
            }

            // handles primes of form 30 * k + 13
            for (;;) {
                case 24: {
                            std::size_t maxOffset = kValue * 28U + 12U; // 
                            std::size_t unrollLimit = std::max(sieveSize, maxOffset) - maxOffset;
                            for (; byteIndex < unrollLimit; byteIndex += kValue * 30U + 13U) {
                                sieve[byteIndex + kValue *  0U +  0U] &= MASK0;
                                sieve[byteIndex + kValue *  6U +  3U] &= MASK0;
                                sieve[byteIndex + kValue * 10U +  4U] &= MASK0;
                                sieve[byteIndex + kValue * 12U +  5U] &= MASK0;
                                sieve[byteIndex + kValue * 16U +  7U] &= MASK0;
                                sieve[byteIndex + kValue * 18U +  8U] &= MASK0;
                                sieve[byteIndex + kValue * 22U +  9U] &= MASK0;
                                sieve[byteIndex + kValue * 28U + 12U] &= MASK0;
                            }
                            IS_DONE(24); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 3; [[fallthrough]];
                        }
                case 25: IS_DONE(25); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 1; [[fallthrough]];
                case 26: IS_DONE(26); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
                case 27: IS_DONE(27); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 2; [[fallthrough]];
                case 28: IS_DONE(28); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
                case 29: IS_DONE(29); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 1; [[fallthrough]];
                case 30: IS_DONE(30); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 3; [[fallthrough]];
                case 31: IS_DONE(31); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
            }

            // handles primes of form 30 * k + 17
            for (;;) {
                case 32: {
                            std::size_t maxOffset = kValue * 28U + 16U; // 
                            std::size_t unrollLimit = std::max(sieveSize, maxOffset) - maxOffset;
                            for (; byteIndex < unrollLimit; byteIndex += kValue * 30U + 17U) {
                                sieve[byteIndex + kValue *  0U +  0U] &= MASK0;
                                sieve[byteIndex + kValue *  6U +  3U] &= MASK0;
                                sieve[byteIndex + kValue * 10U +  6U] &= MASK0;
                                sieve[byteIndex + kValue * 12U +  7U] &= MASK0;
                                sieve[byteIndex + kValue * 16U +  9U] &= MASK0;
                                sieve[byteIndex + kValue * 18U + 10U] &= MASK0;
                                sieve[byteIndex + kValue * 22U + 13U] &= MASK0;
                                sieve[byteIndex + kValue * 28U + 16U] &= MASK0;
                            }
                            IS_DONE(32); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 3; [[fallthrough]];
                        }
                case 33: IS_DONE(33); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 3; [[fallthrough]];
                case 34: IS_DONE(34); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
                case 35: IS_DONE(35); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 2; [[fallthrough]];
                case 36: IS_DONE(36); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
                case 37: IS_DONE(37); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 3; [[fallthrough]];
                case 38: IS_DONE(38); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 3; [[fallthrough]];
                case 39: IS_DONE(39); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
            }

            // handles primes of form 30 * k + 19
            for (;;) {
                case 40: {
                            std::size_t maxOffset = kValue * 28U + 18U; // 
                            std::size_t unrollLimit = std::max(sieveSize, maxOffset) - maxOffset;
                            for (; byteIndex < unrollLimit; byteIndex += kValue * 30U + 19U) {
                                sieve[byteIndex + kValue *  0U +  0U] &= MASK0;
                                sieve[byteIndex + kValue *  6U +  4U] &= MASK0;
                                sieve[byteIndex + kValue * 10U +  6U] &= MASK0;
                                sieve[byteIndex + kValue * 12U +  8U] &= MASK0;
                                sieve[byteIndex + kValue * 16U + 10U] &= MASK0;
                                sieve[byteIndex + kValue * 18U + 12U] &= MASK0;
                                sieve[byteIndex + kValue * 22U + 14U] &= MASK0;
                                sieve[byteIndex + kValue * 28U + 18U] &= MASK0;
                            }
                            IS_DONE(40); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 4; [[fallthrough]];
                        }
                case 41: IS_DONE(41); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 2; [[fallthrough]];
                case 42: IS_DONE(42); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 2; [[fallthrough]];
                case 43: IS_DONE(43); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 2; [[fallthrough]];
                case 44: IS_DONE(44); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 2; [[fallthrough]];
                case 45: IS_DONE(45); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 2; [[fallthrough]];
                case 46: IS_DONE(46); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 4; [[fallthrough]];
                case 47: IS_DONE(47); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
            }

            // handles primes of form 30 * k + 23
            for (;;) {
                case 48: {
                            std::size_t maxOffset = kValue * 28U + 22U; // 
                            std::size_t unrollLimit = std::max(sieveSize, maxOffset) - maxOffset;
                            for (; byteIndex < unrollLimit; byteIndex += kValue * 30U + 23U) {
                                sieve[byteIndex + kValue *  0U +  0U] &= MASK0;
                                sieve[byteIndex + kValue *  6U +  5U] &= MASK0;
                                sieve[byteIndex + kValue * 10U +  8U] &= MASK0;
                                sieve[byteIndex + kValue * 12U + 10U] &= MASK0;
                                sieve[byteIndex + kValue * 16U + 13U] &= MASK0;
                                sieve[byteIndex + kValue * 18U + 14U] &= MASK0;
                                sieve[byteIndex + kValue * 22U + 17U] &= MASK0;
                                sieve[byteIndex + kValue * 28U + 22U] &= MASK0;
                            }
                            IS_DONE(48); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 5; [[fallthrough]];
                        }
                case 49: IS_DONE(49); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 3; [[fallthrough]];
                case 50: IS_DONE(50); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
                case 51: IS_DONE(51); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 4; [[fallthrough]];
                case 52: IS_DONE(52); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
                case 53: IS_DONE(53); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 3; [[fallthrough]];
                case 54: IS_DONE(54); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 5; [[fallthrough]];
                case 55: IS_DONE(55); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
            }

            // handles primes of form 30 * k + 29
            for (;;) {
                case 56: {
                            std::size_t maxOffset = kValue * 28U + 28U; // 
                            std::size_t unrollLimit = std::max(sieveSize, maxOffset) - maxOffset;
                            for (; byteIndex < unrollLimit; byteIndex += kValue * 30U + 29U) {
                                sieve[byteIndex + kValue *  0U +  0U] &= MASK0;
                                sieve[byteIndex + kValue *  6U +  6U] &= MASK0;
                                sieve[byteIndex + kValue * 10U + 10U] &= MASK0;
                                sieve[byteIndex + kValue * 12U + 12U] &= MASK0;
                                sieve[byteIndex + kValue * 16U + 16U] &= MASK0;
                                sieve[byteIndex + kValue * 18U + 18U] &= MASK0;
                                sieve[byteIndex + kValue * 22U + 22U] &= MASK0;
                                sieve[byteIndex + kValue * 28U + 28U] &= MASK0;
                            }
                            IS_DONE(56); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 6; [[fallthrough]];
                        }
                case 57: IS_DONE(57); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 4; [[fallthrough]];
                case 58: IS_DONE(58); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 2; [[fallthrough]];
                case 59: IS_DONE(59); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 4; [[fallthrough]];
                case 60: IS_DONE(64); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 2; [[fallthrough]];
                case 61: IS_DONE(64); sieve[byteIndex] &= MASK0; byteIndex += kValue * 4 + 4; [[fallthrough]];
                case 62: IS_DONE(64); sieve[byteIndex] &= MASK0; byteIndex += kValue * 6 + 6; [[fallthrough]];
                case 63: IS_DONE(64); sieve[byteIndex] &= MASK0; byteIndex += kValue * 2 + 1; [[fallthrough]];
            }

            default: UNREACHABLE;
        }

        next_prime:;
    }
}
}

