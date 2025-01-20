#ifndef TEXT_TO_PRIMES_HPP
#define TEXT_TO_PRIMES_HPP

#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"


namespace EndPointConversions {

    /**
     * @brief optimized atoi with spans
     *
     * @param number    the span holding a number in base 10 ascii form
     * @return          uint64_t number from the given string
     *
     * @assumption_1    span size is size of number
     * @assumption_2    span only has 0-9 digits 
     */
    std::uint64_t getNextNumberBase10_XXd(std::span<const std::uint8_t>);
    std::uint64_t getNextNumberBase10(std::span<const std::uint8_t>);

    /**
     * @brief convert block of text to numbers
     * simply feed the params and call to get back converted numbers
     *
     * @param numbers   buffer of text representing the list of numbers
     * @param lengths   lengths of each of the numbers
     * @param primes    a place to sotre the converted prime numbers
     *
     * @assumption_1    numbers are base 10
     * @assumption_2    text only has newlines and digit chars
     * @assumption_3    starts with number and ends with '\n'
     * @assumption_4    primes big enough to hold converted data 
     */
    void convertTextBlock(std::span<const std::uint8_t>, std::span<const std::size_t>, std::span<std::uint64_t>);
}
#endif
