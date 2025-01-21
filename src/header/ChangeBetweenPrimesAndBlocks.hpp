#ifndef CHANGE_BETWEEN_PRIMES_AND_BLOCKS_HPP
#define CHANGE_BETWEEN_PRIMES_AND_BLOCKS_HPP

#include "ContainerIncludes.hpp"
#include "FastMath.hpp"
#include "IntegralTypeIncludes.hpp"
#include "ProjectConstants.hpp"

namespace EndpointConversion {
    void decompressBlock(const std::span<std::uint8_t>, std::vector<std::uint64_t>, std::uint64_t);
    /**
     * @brief call to extra prime number from compressed byte.
     *
     * @param block Is the offset which our prime is at.
     * @param mask  Holds the next prime in byte form.
     * @return 8 byte prime number
     */
    std::uint64_t extractNextPrime(std::uint64_t, std::uint8_t);

    /**
     * @brief Call to compress a block of prime numbers into bytes.
     *
     * @param primesIn  Span of primes in 8 byte form.
     * @param primesOut List of bytes representing the compressed primes.
     */
    void compressBlock(const std::span<std::uint64_t>, std::vector<std::uint8_t>);

    /**
     * @brief Call to extract a list of primes from a block of bytes.
     *
     * @param primesIn  Span of bytes representing the compressed primes.
     * @param primesOut List of 8 byte numbers to store the primes in.
     * @param offset    The starting point that our compressed primes start at.
     */
    void decompressBlock(const std::span<std::uint8_t>, std::vector<std::uint64_t>, std::uint64_t);
}

#endif
