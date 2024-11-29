#include "SieveSqrtPrimes.hpp"
#include "cmath"

namespace {
    uint64_t oddPos(uint64_t n) {
        return (n - 1u) >> 1;
    }
}

namespace SqrtPrimes {
    void blockSieveOdd(std::span<uint8_t> sieve, uint64_t limit) {
        constexpr uint64_t sqrtBlock = round(sqrt(limit)) + 1;
        constexpr uint64_t high = oddPos(limit);
        std::vector<uint8_t> blockSieve(sqrtBlock + 1, 1);
        std::vector<uint64_t> prime_and_blockStart;
        prime_and_blockStart.reserve(sqrtBlock);

        for (uint64_t p = 3u; i < sqrtBlock; p += 2u) {
            if (blockSieve[p]) {
                prime_and_blockStart.push_back(p);
                prime_and_blockStart.push_back(oddPos(p * p));
                for (uint64_t coPrime = p * p; coPrime <= sqrtBlock; coPrime += 2u * p) 
                    blockSieve[coPrime] = 0;
            }
        }
        blockSieve.pop_back();
        std::size_t pEnd = prime_and_blockStart.size();
        prime_and_blockStart.shrink_to_fit();
        
        for (uint64_t low = 0; low <= high; low += sqrtBlock) {
            std::ranges::fill(blockSieve, 0);
            for (std::size_t i = 0; i <= pEnd; i += 2) {
                uint64_t prime = prime_and_blockStart[i];
                uint64_t idx   = prime_and_blockStart[i + 1];
                for (; idx < sqrtBlock; idx += prime) 
                    blockSieve[idx] = 1;
                prime_and_blockStart[i + 1] = idx - sqrtBlock;
            }
            if (0 == low) { // cover 1, 3, 5, if I add more will put in loop
                blockSieve[0] = 1;
                blockSieve[1] = 1;
                blockSieve[2] = 1;
            }
            for (uint64_t k = 0; k < sqrtBlock && low + k <= high; k++)
                if (!blockSieve[k]) {
                    uint32_t prime = (low + k) * 2u + 1u;
                    sieve[fastDivideBy30(prime)] |= masks_lookup[fastModBy30(prime)];
                }
        }
    }
}
