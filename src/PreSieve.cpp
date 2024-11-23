#include "header/PreSieve.hpp"

// TODO fix namespace name MAYBE
// TODO apply these functions to a class based solution
// TODO move the presieves into this namespace even if they are stored
namespace PreSieve {
    void applyPreSieve(std::span<uint8_t> sieve, std::span<uint8_t> preSieve) {
        // Step 1: find start point of presieve with math
        // Step 2: apply the preseive from start
        // Step 3: loop i = end point of start -> till can't apply full preSieve
        //      for each iteration apply bitwise ad of presieve to sieve
        // Step 4: apply the last preseive difference
        //      can be done in loop at a bit of cost or outside after
        // Optimization would be doing multiple presieves at once a &= (b & c &d)
        // or explicitly applying multiple indexes at same time or both
    }

    void applyPreSieves(std::span<uint8_t> sieve) {
        // Step 0: fill(sieve, 255U); // make it named literal? optional if not done
        // Step 1: Loop each preSieve we have
        //      each iteration call applyPreSieve(sieve, span(next_presieve)) ??
        // Optimization apply what is said in other function here?
    }
}
