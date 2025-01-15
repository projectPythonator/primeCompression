#ifndef PRIMES_TO_TEXT_HPP
#define PRIMES_TO_TEXT_HPP

#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"


namespace EndPointConversions {
    // change this to 3 functions with asserts 9, 16, and 20
    void addChunkBase10ToBuffer(std::span<std::uint8_t>, std::uint32_t);

    void addNumberBase10ToBuffer(std::span<std::uint8_t>, std::uint64_t);

    std::size_t convertPrimesBlock(std::span<const std::uint64_t>, std::span<std::uint8_t>);
}
#endif
