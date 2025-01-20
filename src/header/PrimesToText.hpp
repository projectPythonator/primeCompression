#ifndef PRIMES_TO_TEXT_HPP
#define PRIMES_TO_TEXT_HPP

#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"
#include "UtilityIncludes.hpp"


namespace EndPointConversions {
    /**
     * @brief convert number n to string and store it in the span
     *
     * @assumption_1    no prime is 0
     */
    void addNextNumberBase10_XXd(std::span<std::uint8_t>, std::uint64_t);
    void addNextNumberBase10(std::span<std::uint8_t>, std::uint64_t);

    /**
     * @brief convert list of numbers into a buffer
     * call with the params and you will recieve a buffer of text in numbers
     *
     * @param primes    a list of primes to convert
     * @param numbers   buffer to hold the output
     * @return  end index of the buffer
     *
     * @assumption_1    numbers is big enough to hold primes
     * @assumption_1    no prime is 0
     */
    std::size_t convertPrimesBlock(std::span<const std::uint64_t>, std::span<std::uint8_t>);
}
#endif
