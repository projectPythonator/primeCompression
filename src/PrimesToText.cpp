#include "header/PrimesToText.hpp"

namespace {
    constexpr std::uint8_t nl_zero = '\n'-'0';

    constexpr std::size_t max_9_digit  = 10u;
    constexpr std::size_t max_16_digit = 17u;
    constexpr std::size_t max_20_digit = 21u;
    constexpr std::uint8_t base = 10u;

    // represents functions to use, 0-9 is _9d, 10-16 is _16d, and the rest are _20d
    constexpr int size_lookup[max_20_digit] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2};

    constexpr std::uint64_t log_10_lookup[max_20_digit] = 
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
            if (n >= log_10_lookup[i])
                return i;
        return 64u;
    }

    void addNextNumberBase10_9d(const std::span<std::uint8_t> number, std::uint32_t n) {
        assert(number.size() < max_9_digit); // do I need this? maybe
        for (std::uint8_t &digit: number) {
            digit = n % base;
            n /= base;
        }
        std::reverse(number.begin(), number.end());
        // use code below if above is too slow
        /*
        std::uint8_t buf[max_9_digit] = {0};
        std::size_t b = 0;
        do {
            buf[b++] = n % base;
            n /= base;
        } while (b < number.size());
        std::memcpy(number.data(), buf, number.size());
        */
    }

    void addNextNumberBase10_16d(const std::span<std::uint8_t> number, std::uint64_t n) {
        assert(number.size() < max_16_digit); // do I need this? maybe
        for (std::uint8_t &digit: number) {
            digit = n % base;
            n /= base;
        }
        std::reverse(number.begin(), number.end());

        // use code below if above is too slow
        /*
        std::uint8_t buf[max_16_digit] = {0};
        std::size_t b = 0;
        do {
            buf[b++] = (uint32_t)n % base;
            n /= base;
        } while (b < number.size());
        std::memcpy(number.data(), buf, number.size());
        */
    }

    void addNextNumberBase10_20d(const std::span<std::uint8_t> number, std::uint64_t n) {
        assert(number.size() < max_20_digit); // do I need this? maybe
        for (std::uint8_t &digit: number) {
            digit = n % base;
            n /= base;
        }
        std::reverse(number.begin(), number.end());
        // use code below if above is too slow
        /*
        std::uint8_t buf[max_20_digit] = {0};
        std::size_t b = 0;
        #pragma GCC unroll 4
        do {
            buf[b++] = n % base;
            n /= base;
        } while (b < number.size());
        std::memcpy(number.data(), buf, number.size());
        */
    }
}

namespace EndPointConversions {
    /**
     * @brief convert number to string optimized see below
     */
    void addNextNumberBase10_XXd(std::span<std::uint8_t> num, std::uint64_t n) {
        // can probably change these into function pointers maybe
        assert(num.size() < max_20_digit); 
        switch(size_lookup[num.size()]) {
            case 0: addNextNumberBase10_9d(num, (uint32_t)n); break;
            case 1: addNextNumberBase10_16d(num, n);         break;
            case 2: addNextNumberBase10_20d(num, n);         break;
            default: perror("assert check Failed"); return;
        }
    }

    /**
     * @brief convert number to string
     *
     * @param numbers   buffer to store number in
     * @param n         number to convert 
     * @return  end index of the buffer
     *
     * @optimizatiion_1 unroll size vs let compiler do it
     *
     * @assumption_1    no prime is 0
     */
    void addNextNumberBase10(const std::span<std::uint8_t> num, std::uint64_t n) {
        assert(num.size() < max_20_digit); // do I need this? maybe
        #pragma GCC unroll 4
        for (std::uint8_t &digit: num) {
            digit = n % base;
            n /= base;
        }
        std::reverse(num.begin(), num.end());
    }

    /**
     * @brief convert list of numbers into a buffer
     * convert list of numbers into base10 ascii char buffer 
     *
     * @param primes    a list of primes to convert
     * @param numbers   buffer to hold the output
     * @return  end index of the buffer
     *
     * @optimizatiion_1 have multiple threads work on section at once. fixed can new queue them up for different sectoins.
     *
     * @assumption_1    numbers is big enough to hold primes
     * @assumption_1    no prime is 0
     */
    std::size_t ToText::convertPrimesBlock(
            const std::span<const std::uint64_t> primes, 
            const std::span<std::uint8_t> nums) {
        std::fill(nums.begin(), nums.end(), nl_zero);
        std::size_t bufferIndex = 0;
        std::size_t currentSize = getNumberSize(primes[0]);
        for (const std::uint64_t &prime: primes) {
            currentSize = getLog10Size(prime, currentSize);
            addNextNumberBase10(nums.subspan(bufferIndex, currentSize), prime);
            bufferIndex += (currentSize + 1);
        }
        return bufferIndex;
    }
}
