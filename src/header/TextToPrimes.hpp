#ifndef TEXT_TO_PRIMES_HPP
#define TEXT_TO_PRIMES_HPP

#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"


namespace EndPointConversions {
    // change this to 3 functions with asserts, 9, 16, 20
    std::uint64_t getNextNumberBase10_XXd(std::span<const std::uint8_t>);
    std::uint64_t getNextNumberBase10(std::span<const std::uint8_t>);

    void convertTextBlock(std::span<const std::uint8_t>, std::span<const std::size_t>, std::span<std::uint64_t>);
}
#endif
