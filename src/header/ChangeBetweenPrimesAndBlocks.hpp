#ifndef CHANGE_BETWEEN_PRIMES_AND_BLOCKS_HPP
#define CHANGE_BETWEEN_PRIMES_AND_BLOCKS_HPP

#include "ContainerIncludes.hpp"
#include "FastMath.hpp"
#include "IntegralTypeIncludes.hpp"
#include "ProjectConstants.hpp"

namespace EndpointConversion {
    std::uint64_t extractNextPrime(std::uint64_t, std::uint8_t);
    void compressBlock(const std::span<std::uint64_t>, std::vector<std::uint8_t>);
    void decompressBlock(const std::span<std::uint8_t>, std::vector<std::uint64_t>, std::uint64_t);
}

#endif
