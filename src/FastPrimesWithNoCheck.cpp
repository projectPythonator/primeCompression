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

