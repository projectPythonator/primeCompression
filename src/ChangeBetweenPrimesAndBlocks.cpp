#include "header/ChangeBetweenPrimesAndBlocks.hpp"

namespace EndpointConversion {
    /**
     * @brief extract next prime from mask
     * a compressed prime is 30 * byte_index + mask_offset
     *
     * @param block is the offset which our prime is at
     * @param mask holds the next prime in byte form
     * @return 8 byte prime number
     */
    std::uint64_t extractNextPrime(std::uint64_t block, std::uint8_t mask) {
        return ProjectConstants::primorial_values[ProjectConstants::rb5_index] * block 
            + ProjectConstants::mask_to_offset[(-mask & mask)];
    }

    /**
     * @brief compress primes
     * Given list of existing primes compress them.
     *
     * @param primesIn  Span of primes in 8 byte form.
     * @param primesOut List of bytes representing the compressed primes.
     *
     * @optimization_1 change vector type to array and have static size.
     * @optimization_2 change inner function calls to / and % right now from my ad hoc profiling
     *  the function call variants are fast but consistent and the / % is sometimes a bit faster
     *  and sometimes was a bit slower. Was ad hoc because not tested on this program just raw
     *  speed. The calls were consistent though so will use them until this is a bottle neck.
     */
    void compressBlock(const std::span<std::uint64_t> primesIn, std::vector<std::uint8_t> primesOut) {
        std::size_t blockSize = FastMath::fastDivideBy30(primesIn.back()) - FastMath::fastDivideBy30(primesIn.front());
        primesOut.assign(blockSize, 0); // this might need to be moved along with line above it.
        for(const auto& prime: primesIn)
            primesOut[FastMath::fastDivideBy30(prime) % blockSize] |= ProjectConstants::offset_to_mask[FastMath::fastModBy30(prime)];
    }

    /**
     * @brief extract primes
     * Extract compressed primes stored in bytes and convert them to a list of 8 byte numbers.
     *
     * @param primesIn  Span of bytes representing the compressed primes.
     * @param primesOut List of 8 byte numbers to store the primes in.
     * @param offset    The starting point that our compressed primes start at.
     *
     * @optimization_1 can replace push_back with indexing if you create with enough space or calc the popcount.
     * @optimization_2 run sections in parallel maybe that work on different sections of a block.
     */
    void decompressBlock(const std::span<std::uint8_t> primesIn, std::vector<std::uint64_t> primesOut, std::uint64_t offset) {
        primesOut.reserve(8 * primesIn.size());
        for (std::size_t i = 0; i < primesIn.size(); i++)
            if (primesIn[i]) // blocks with primes require bits to be on 
                for (std::uint8_t mask = primesIn[i]; mask; mask ^= (-mask & mask)) // turn off lsb each iteration
                    primesOut.push_back(extractNextPrime(offset + i, mask));
        primesOut.shrink_to_fit();
    }
}
