#include "header/SieveSegment.hpp"

namespace {
    std::size_t jump_lookup[8];

    void setJumpsForPrime(std::uint64_t prime) {
        for (std::size_t coPrime = prime, i = 0; i < 8; i++) {
            jump_lookup[i] = FastMath::fastDivideBy30(coPrime);
            coPrime += (prime * ProjectConstants::jumps[i]);
        }
    }

    void sievePrime(std::span<std::uint8_t> segment, std::uint64_t prime) {
        setJumpsForPrime(prime);
        for (std::size_t i = 0; i < segment.size(); i += prime) {
            std::size_t j = 0;
            for (const std::uint8_t &mask: ProjectConstants::mask_lookup[prime])
                segment[i + jump_lookup[j++]] &= mask;
        }
    }
}

namespace SieveSegment {

     /**
     * @brief build the sieve needed for program 
     * Using sieving method we make a partial sieve to represent wheel upto the Nth prime after 5
     *
     * @param segment   the "sieve" to hold the rb5 based sieving holds bytes the represent our rb5 class to show primes
     * @param level     the level to which we need to sieve upto its basically the a stop at nth prime type thing 
     *
     * @optimizatiion_1 maybe unroll the loop if possible
     * @bug             we don't check to ensure segment is right size yet need to add assert for that or something
     */
    void sieveSegment(std::span<std::uint8_t> segment, std::size_t level) {
        if (level < 2) // since are sieving for rb5 to rbX X>5 doesn't make sense to do level 1
            return;

        std::fill(segment.begin(), segment.end(), 255u);    // all bits turned on initially 
        for (std::size_t i = 1; i <= level; i++)            // then turn them off in this loop
            sievePrime(segment, ProjectConstants::primes_after_5[i]);
    }
}
