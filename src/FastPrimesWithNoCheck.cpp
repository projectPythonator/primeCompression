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
            // current prime is prime % 30 == 1
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

            default: UNREACHABLE;
        }

        next_iteration:;
    }
}
}

