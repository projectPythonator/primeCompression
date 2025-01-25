#include "header/ChangeBetweenPrimesAndBlocks.hpp"

// TODO look into making this a class
//  - two classes
//  - going from num -> bytes has bytes as the data being worked on
//  - going from bytes -> nums has numbers as the data being worked on
//  - this might allow us to deal with stuff better
namespace EndpointConversion {
    /**
     * @brief Get amount of bytes needed to hold range of primes.
     *
     * @param lo    lower inclusive bound.
     * @param hi    upper inclusive bound.
     * @return      Smallest block to fix the range between two primes.
     */
    std::size_t blockSize(std::uint64_t lo, std::uint64_t hi) {
        return FastMath::fastDivideBy30(hi) - FastMath::fastDivideBy30(lo);
    }

    /**
     * @brief Quickly getting bit count.
     *
     * @param block Span of compressed primes.
     * @return      Number of bits set.
     */
    std::size_t blockPopcount(const std::span<const std::uint8_t> block) {
        assert(block.size() > 0);
        std::size_t result = 0;
        for (const std::uint8_t &el: block)
            result += std::popcount(el);
        return result;
    }

    /**
     * @brief Resize vector to fit prime range.
     *
     * @param primesIn  Span of numbers holding primes.
     * @param primesOut Vector of bytes to resize.
     * @assumption      primesIn size > 1
     */
    void adjustBlockSize(const std::span<const std::uint64_t> primesIn, std::vector<std::uint8_t> primesOut) {
        primesOut.resize(blockSize(primesIn.front(), primesIn.back()));
    }

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
    void decompressBlock(
            const std::span<const std::uint8_t> primesIn, 
            const std::span<std::uint64_t> primesOut, 
            std::uint64_t offset) {
        for (std::size_t i = 0, j = 0; i < primesIn.size(); i++)
            if (primesIn[i])    // blocks with primes require bits to be on 
                for (std::uint8_t mask = primesIn[i]; mask; mask ^= (-mask & mask)) // turn off lsb each iteration
                    primesOut[j++] = extractNextPrime(offset + i, mask);
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
     * @assumption      primesOut has been resized properly.
     */
    void compressBlock(
            const std::span<const std::uint64_t> primesIn, 
            const std::span<std::uint8_t> primesOut) {
        std::fill(primesOut.begin(), primesOut.end(), 0);
        for(const auto& prime: primesIn)
            primesOut[FastMath::fastDivideBy30(prime) % primesOut.size()] |= ProjectConstants::offset_to_mask[FastMath::fastModBy30(prime)];
    }
}
