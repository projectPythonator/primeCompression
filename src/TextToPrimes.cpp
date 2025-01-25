#include "header/TextToPrimes.hpp"

namespace {
    constexpr std::size_t max_9_digit  = 10u;
    constexpr std::size_t max_16_digit = 17u;
    constexpr std::size_t max_20_digit = 21u;
    constexpr std::uint64_t base = 10u;

    // represents functions to use, 0-9 is _9d, 10-16 is _16d, and the rest are _20d
    constexpr int size_lookup[max_20_digit] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2};

    std::uint32_t getNextNumberBase10_9d(const std::span<const std::uint8_t> number) {
        assert(number.size() < max_9_digit);
        std::uint32_t result = 0;
        for (const std::uint8_t &digit: number) 
            result = result * base + digit;
        // use if above is slower, the asm unrolls so idk if its better
        //for (std::size_t b = 0; b < number.size(); b++) 
        //    result = result * base + number[b];
        return result;
    }

    std::uint64_t getNextNumberBase10_16d(const std::span<const std::uint8_t> number) {
        assert(number.size() < max_16_digit);
        std::uint64_t result = 0;
        for (const std::uint8_t &digit: number) 
            result = result * base + digit;
        // use if above is slower, the asm unrolls so idk if its better
        //for (std::size_t b = 0; b < number.size(); b++) 
        //    result = result * base + number[b];
        return result;
    }

    std::uint64_t getNextNumberBase10_20d(const std::span<const std::uint8_t> number) {
        assert(number.size() < max_20_digit); // do I need this? maybe
        std::uint64_t result = 0;
        #pragma GCC unroll 8 // need to add in clang and mvvc
        for (const std::uint8_t &digit: number) 
            result = result * base + digit;
        // use if above is slower, the asm unrolls so idk if its better
        //for (std::size_t b = 0; b < number.size(); b++) 
        //    result = result * base + number[b];
        return result;
    }

}

namespace EndPointConversions {
    /**
     * @brief See below for more info
     *
     * @optimizatiion   applies unroll and size based optimization not even sure if it fully is better
     */
    std::uint64_t getNextNumberBase10_XXd(const std::span<const std::uint8_t> number) {
        // can probably change these into function pointers maybe
        assert(number.size() < max_20_digit); 
        switch(size_lookup[number.size()]) {
            case 0: return (std::uint64_t) getNextNumberBase10_9d(number);
            case 1: return getNextNumberBase10_16d(number);
            case 2: return getNextNumberBase10_20d(number);
            default: perror("assert check Failed"); return 0;
        }
    }

    /**
     * @brief Grabs next number from a char buffer
     * Using this method we can quickly grab a long long from a buffer with or without multithreading
     *
     * @param number    the span holding a number in base 10 ascii form
     * @return          uint64_t number from the given string
     *
     * @optimizatiion_1 maybe unroll the loop if possible
     * @assumption      strings will not be checked for 0-9 assumes correct input will probably crash if happens
     */
    std::uint64_t getNextNumberBase10(const std::span<const std::uint8_t> number) {
        std::uint64_t result = 0;
        #pragma GCC unroll 8 // need to add in clang and mvvc
        for (const std::uint8_t &digit: number)
            result = result * base + digit;
        return result;
    }

    /**
     * @brief convert block of text to numbers
     * Using a formatted proper block of text we convert them to numbers 
     *
     * @param numbers   buffer of text representing the list of numbers
     * @param lengths   lengths of each of the numbers
     * @param primes    a place to sotre the converted prime numbers
     *
     * @optimizatiion_1 have multiple threads work on section at once 
     * @optimizatiion_2 change legnths to be length_x, start, end type of thing
     *
     * @assumption_1    numbers are base 10
     * @assumption_2    text only has newlines and digit chars
     * @assumption_3    starts with number and ends with '\n'
     */
    void convertTextBlock(
            std::span<const std::uint8_t> numbers, 
            std::span<const std::size_t> lengths, 
            std::span<std::uint64_t> primes) {
        std::size_t bufferIndex = 0;
        std::size_t primesIndex = 0;
        for (const std::size_t length: lengths) {
            primes[primesIndex++] = getNextNumberBase10(numbers.subspan(bufferIndex, length));
            bufferIndex += (length + 1);
        }
    }
}
