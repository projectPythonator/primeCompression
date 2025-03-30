#include "header/PrimesToText.hpp"
#include <cstdlib>

namespace {
    constexpr std::uint8_t nl_zero = '\n'-'0';

    constexpr std::size_t digit_count_size  = 65u;
    constexpr std::size_t max_9_digit  = 10u;
    constexpr std::size_t max_16_digit = 17u;
    constexpr std::size_t max_20_digit = 21u;
    constexpr std::uint8_t base = 10u;

    // represents functions to use, 0-9 is _9d, 10-16 is _16d, and the rest are _20d
    constexpr int size_lookup[max_20_digit] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2};

    constexpr int digit_table[digit_count_size] = {
        19, 19, 19, 19, 18, 18, 18,
        17, 17, 17, 16, 16, 16,
        16, 15, 15, 15, 14, 14, 14,
        13, 13, 13, 13, 12, 12,
        12, 11, 11, 11, 10, 10, 10,
        10,  9,  9,  9,  8,  8,
         8,  7,  7,  7,  7,  6,  6,
         6,  5,  5,  5,  4,  4,
         4,  4,  3,  3,  3,  2,  2,
         2,  1,  1,  1,  1,  1};

    constexpr std::uint64_t log_table[digit_count_size] = {
        1844674407370955161ULL, 
        1844674407370955161ULL, 
        1844674407370955161ULL, 
        1844674407370955161ULL, 
        999999999999999999ULL,
        999999999999999999ULL,
        999999999999999999ULL,
        99999999999999999ULL,
        99999999999999999ULL,
        99999999999999999ULL,
        9999999999999999ULL,
        9999999999999999ULL,
        9999999999999999ULL,
        9999999999999999ULL,
        999999999999999ULL,
        999999999999999ULL,
        999999999999999ULL,
        99999999999999ULL,
        99999999999999ULL,
        99999999999999ULL,
        9999999999999ULL,
        9999999999999ULL,
        9999999999999ULL,
        9999999999999ULL,
        999999999999ULL,
        999999999999ULL,
        999999999999ULL,
        99999999999ULL,
        99999999999ULL,
        99999999999ULL,
        9999999999ULL,
        9999999999ULL,
        9999999999ULL,
        9999999999ULL,
        999999999ULL,
        999999999ULL,
        999999999ULL,
        99999999ULL,
        99999999ULL,
        99999999ULL,
        9999999ULL,
        9999999ULL,
        9999999ULL,
        9999999ULL,
        999999ULL,
        999999ULL,
        999999ULL,
        99999ULL,
        99999ULL,
        99999ULL,
        9999ULL,
        9999ULL,
        9999ULL,
        9999ULL,
        999ULL,
        999ULL,
        999ULL,
        99ULL,
        99ULL,
        99ULL,
        9ULL,
        9ULL,
        9ULL,
        9ULL,
        0ULL};

    constexpr std::uint64_t log_10_lookup[max_20_digit] = {
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

    std::size_t countDigits(std::uint64_t n) {
        int log2 = std::countl_zero(n);
        std::uint64_t lo = log_table[log2];
        std::uint64_t hi = digit_table[log2];
        return (n > lo) + hi;
    }

    void addNextNumberBase10_9d(const std::span<std::uint8_t> number, std::uint32_t n) {
        assert(number.size() < max_9_digit); // do I need this? maybe
        for (std::size_t b = 0, i = number.size() - 1; b < number.size(); b++) {
            number[i--] = n % base;
            n /= base;
        }
    }

    void addNextNumberBase10_16d(const std::span<std::uint8_t> number, std::uint64_t n) {
        assert(number.size() < max_16_digit); // do I need this? maybe
        for (std::size_t b = 0, i = number.size() - 1; b < number.size(); b++) {
            number[i--] = n % base;
            n /= base;
        }
    }

    void addNextNumberBase10_20d(const std::span<std::uint8_t> number, std::uint64_t n) {
        assert(number.size() < max_20_digit); // do I need this? maybe
        std::size_t b = 0, i = number.size() - 1;
        for (; b + 4 < number.size(); b += 4) {
            number[i--] = n % base;
            n /= base;
            number[i--] = n % base;
            n /= base;
            number[i--] = n % base;
            n /= base;
            number[i--] = n % base;
            n /= base;
        }
        for (; b < number.size(); b++) {
            number[i--] = n % base;
            n /= base;
        }
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
        assert(num.size() < max_20_digit); 
        for (std::size_t b = 0, i = number.size() - 1; b < number.size(); b++) {
            number[i--] = n % base;
            n /= base;
        }
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
        std::size_t currentSize = countDigits(primes[0]);
        for (const std::uint64_t &prime: primes) {
            currentSize = getLog10Size(prime, currentSize);
            addNextNumberBase10(nums.subspan(bufferIndex, currentSize), prime);
            bufferIndex += (currentSize + 1);
        }
        return bufferIndex;
    }
}
