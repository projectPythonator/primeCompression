#include "header/SieveSegment.hpp"

namespace {
    std::size_t jump_lookup[8];

    void setJumpsForPrime(std::uint64_t prime) {
        for (std::size_t coPrime = prime, i = 0; i < 8; i++) {
            jump_lookup[i] = fastDivideBy30(coPrime);
            coPrime += (prime * ProjectConstants::jumps[i]);
        }
    }
}

namespace pending {
    void sievePrime(std::span<std::uint8_t segment, std::uint64_t prime) {
        setJumpsForPrime(prime);
        for (std::size_t i = 0; i < segment.size(); i += prime) {
            auto j = 0;
            for (const std::uint8_t mask: ProjectConstants::mask_lookup[prime])
                segment[i + jump_lookup[j++]] &= mask;
        }
    }

    void sieveSegment(std::span<std::uint8_t> segment, std::size_t level) {
        if (level < 2) 
            return;
        std::fill(segment.begin(), segment.end(), 255u);

        for (std::size_t i = 1; i <= level; i++) 
            sievePrime(segment, ProjectConstants::primes_after_5[i]);
    }
}
