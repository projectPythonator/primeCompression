#include "header/TextToPrimes.hpp"
#include <cassert>

namespace {
    constexpr std::size_t max_9_digit  = 10u;
    constexpr std::size_t max_16_digit = 17u;
    constexpr std::size_t max_20_digit = 21u;
    constexpr std::uint64_t base = 10u;
}

namespace EndPointConversions {
    // change this to 3 functions with asserts, 9, 16, 20
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
