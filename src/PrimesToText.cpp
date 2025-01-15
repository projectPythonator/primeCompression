#include "header/PrimesToText.hpp"

namespace {
    constexpr std::uint8_t nl_zero = '\n'-'0';
    constexpr std::uint8_t base = 10u;
    constexpr std::uint32_t chunk_8 = 1000000000u;

    constexpr std::size_t max_size = 8u;

    constexpr std::uint64_t log_10_lookup[21] = 
    {
    1ull, 
    10ull, 
    100ull, 
    1000ull, 
    10000ull, 
    100000ull, 
    1000000ull, 
    10000000ull, 
    100000000ull, 
    1000000000ull, 
    10000000000ull, 
    100000000000ull, 
    1000000000000ull, 
    10000000000000ull, 
    100000000000000ull, 
    1000000000000000ull, 
    10000000000000000ull, 
    100000000000000000ull, 
    1000000000000000000ull, 
    10000000000000000000ull, 
    10000000000000000000ull};
    
    std::size_t getLog10Size(std::uint64_t n, std::size_t prevSize) {
        return (n < log_10_lookup[prevSize])? prevSize: prevSize + 1;
    }

    std::size_t getNumberSize(std::uint64_t n) {
        for (std::size_t i = 20; i > 0; i--) 
            if (n < log_10_lookup[i])
                return i;
        return 64u;
    }
}

namespace EndPointConversions {
    // change this to 3 functions with asserts 9, 16, and 20
    void addChunkBase10ToBuffer(std::span<std::uint8_t> number, std::uint32_t n) {
        std::uint8_t buf[max_size] = {0};
        std::size_t b = 0;
        do {
            buf[b++] = n % base;
            n /= base;
        } while (b < number.size());
        std::memcpy(number.data(), buf, number.size());
    }

    void addNumberBase10ToBuffer(std::span<std::uint8_t> number, std::uint64_t n) {
        for (std::size_t i = 0; i < number.size(); i += 8) {
            addChunkBase10ToBuffer(number.subspan(i, std::min(i, number.size()) - i), n % chunk_8);
            n /= chunk_8;
        }
        std::reverse(number.begin(), number.end());
    }

    std::size_t convertPrimesBlock(std::span<const std::uint64_t> primes, std::span<std::uint8_t> numbers) {
        std::fill(numbers.begin(), numbers.end(), nl_zero);
        std::size_t bufferIndex = 0;
        std::size_t currentSize = getNumberSize(primes[0]);
        for (const std::uint64_t prime: primes) {
            currentSize = getLog10Size(prime, currentSize);
            addNumberBase10ToBuffer(numbers.subspan(bufferIndex, currentSize), prime);
            bufferIndex += (currentSize + 1);
        }
        return bufferIndex;
    }
}
