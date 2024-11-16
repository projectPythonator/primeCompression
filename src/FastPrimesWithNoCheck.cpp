// not sure what includes I will need for this file
#include "rb5GlobalConstants.h"

namespace sieveCompress {


// TODO needs class extention
// TODO typing of sieve needs fixed
// in our case I am not sure if sieve size is needed 
// its here for potential portablility
// TODO check how expensive cleaning up magic numbers is
void crossOff(
        uint8_t *sieve, 
        std::size_t sieveSize, 
        std::size_t startIndex, 
        std::size_t endIndex) {
    
    for (std::size_t primeIndex = startIndex; primeIndex < endIndex; primeIndex++) {

        std::size_t maskIndex; // I am split on what type this should have 
        switch (maskIndex) {
            // handles primes of form 30 * k + 1
            for (;;) {
                case 0: {
                            continue;
                        }
                case 1: continue;
                case 2: continue;
                case 3: continue;
                case 4: continue;
                case 5: continue;
                case 6: continue;
                case 7: continue;
            }

            // handles primes of form 30 * k + 7
            for (;;) {
                case  8: {
                            continue;
                         }
                case  9: continue;
                case 10: continue;
                case 11: continue;
                case 12: continue;
                case 13: continue;
                case 14: continue;
                case 15: continue;
            }

            // handles primes of form 30 * k + 11
            for (;;) {
                case 16: {
                            continue;
                        }
                case 17: continue;
                case 18: continue;
                case 19: continue;
                case 20: continue;
                case 21: continue;
                case 22: continue;
                case 23: continue;
            }

            // handles primes of form 30 * k + 13
            for (;;) {
                case 24: {
                            continue;
                        }
                case 25: continue;
                case 26: continue;
                case 27: continue;
                case 28: continue;
                case 29: continue;
                case 30: continue;
                case 31: continue;
            }

            // handles primes of form 30 * k + 17
            for (;;) {
                case 32: {
                            continue;
                        }
                case 33: continue;
                case 34: continue;
                case 35: continue;
                case 36: continue;
                case 37: continue;
                case 38: continue;
                case 39: continue;
            }

            // handles primes of form 30 * k + 19
            for (;;) {
                case 40: {
                            continue;
                        }
                case 41: continue;
                case 42: continue;
                case 43: continue;
                case 44: continue;
                case 45: continue;
                case 46: continue;
                case 47: continue;
            }

            // handles primes of form 30 * k + 23
            for (;;) {
                case 48: {
                            continue;
                        }
                case 49: continue;
                case 50: continue;
                case 51: continue;
                case 52: continue;
                case 53: continue;
                case 54: continue;
                case 55: continue;
            }

            // handles primes of form 30 * k + 29
            for (;;) {
                case 56: {
                            continue;
                        }
                case 57: continue;
                case 58: continue;
                case 59: continue;
                case 60: continue;
                case 61: continue;
                case 62: continue;
                case 63: continue;
            }

            default: UNREACHABLE;
        }

        next_iteration:;
    }
}
}

