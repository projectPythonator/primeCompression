#include "header/RB5ToPrimes.hpp"


// change namespace name
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
     * @brief Quickly getting bit count.
     *
     * @param block Span of compressed primes.
     * @return      Number of bits set.
     */
    std::size_t blockPopcount(std::span<std::uint8_t> block) {
        assert(block.size() > 0);
        std::size_t result = 0;
        for (const std::uint8_t &el: block)
            result += std::popcount(el);
        return result;
    }

    /**
     * @brief extract primes
     * Extract compressed primes stored in bytes and convert them to a list of 8 byte numbers.
     *
     * @param primesIn  Span of bytes representing the compressed primes.
     * @param primesOut Span of 8 byte numbers to store the primes in.
     * @param offset    The starting point that our compressed primes start at.
     *
     * @optimization_1 can replace push_back with indexing if you create with enough space or calc the popcount.
     * @optimization_2 run sections in parallel maybe that work on different sections of a block.
     * @assumption      primesOut has been resized properly.
     */
    void RB5ToPrimes::decompressBlock(
            const std::span<const std::uint8_t> primesIn, 
            const std::span<std::uint64_t> primesOut, 
            std::uint64_t offset) {
        for (std::size_t i = 0, j = 0; i < primesIn.size(); i++)
            if (primesIn[i])    // blocks with primes require bits to be on 
                for (std::uint8_t mask = primesIn[i]; mask; mask ^= (-mask & mask)) // turn off lsb each iteration
                    primesOut[j++] = extractNextPrime(offset + i, mask);
    }

}
