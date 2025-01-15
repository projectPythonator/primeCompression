#ifndef PRIMES_TO_TEXT_HPP
#define PRIMES_TO_TEXT_HPP

#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"
#include "UtilityIncludes.hpp"


namespace EndPointConversions {
    void addNextNumberBase10_XXd(std::span<std::uint8_t>, std::uint64_t);

    void addNextNumberBase10(std::span<std::uint8_t>, std::uint64_t);

    std::size_t convertPrimesBlock(std::span<const std::uint64_t>, std::span<std::uint8_t>);
}
#endif
