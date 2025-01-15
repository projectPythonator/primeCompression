#include "header/TextToPrimes.hpp"
#include <cassert>

namespace {
    constexpr std::size_t max_9_digit  = 10u;
    constexpr std::size_t max_16_digit = 17u;
    constexpr std::size_t max_20_digit = 21u;
    constexpr std::uint64_t base = 10u;

    // represents functions to use, 0-9 is _9d, 10-16 is _16d, and the rest are _20d
    constexpr int size_lookup[max_20_digit] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2};

    std::uint32_t getNextNumberBase10_9d(std::span<const std::uint8_t> number) {
        assert(number.size() < max_9_digit);
        std::uint32_t result = 0;
        for (std::size_t b = 0; b < number.size(); b++) 
            result = result * base + number[b];
        return result;
    }

    std::uint64_t getNextNumberBase10_16d(std::span<const std::uint8_t> number) {
        assert(number.size() < max_16_digit);
        std::uint64_t result = 0;
        for (std::size_t b = 0; b < number.size(); b++) 
            result = result * base + number[b];
        return result;
    }

    std::uint64_t getNextNumberBase10_20d(std::span<const std::uint8_t> number) {
        assert(number.size() < max_20_digit); // do I need this? maybe
        std::uint64_t result = 0;
        #pragma GCC unroll 4 // need to add in clang and mvvc
        for (std::size_t b = 0; b < number.size(); b++) 
            result = result * base + number[b];
        return result;
    }

}

namespace EndPointConversions {

    std::uint64_t getNextNumberBase10_XXd(std::span<const std::uint8_t> number) {
        // can probably change these into function pointers maybe
        assert(number.size() < max_20_digit); 
        switch(size_lookup[number.size()]) {
            case 0: return (std::uint64_t) getNextNumberBase10_9d(number);
            case 1: return getNextNumberBase10_16d(number);
            case 2: return getNextNumberBase10_20d(number);
            default: perror("assert check Failed"); return 0;
        }
    }

    std::uint64_t getNextNumberBase10(std::span<const std::uint8_t> number) {
        std::uint64_t result = 0;
        for (const std::uint8_t digit: number)
            result = result * base + digit;
        return result;
    }

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
