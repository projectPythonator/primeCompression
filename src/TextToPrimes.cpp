#include "header/TextToPrimes.hpp"

namespace {
    constexpr uint64_t base = 10u;
}

namespace EndPointConversions {
    // change this to 3 functions with asserts, 9, 16, 20
    std::uint64_t getNextNumberBase10(std::span<const std::uint8_t> number) {
        //assert(number.size() < 17)
        // seems to unroll better with assers will profile later
        std::uint64_t result = 0;
        for (std::size_t b = 0; b < number.size(); b++) 
            result = result * base + number[b];
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
