#include "header/PrimesToRB5.hpp"
#include <immintrin.h>

namespace {
    void bitwise_or_assign_simd(
            std::span<std::uint8_t> mainBlock, 
            std::span<std::uint8_t> sideBlock) {
        assert(mainBlock.size() == sideBlock.size());
        assert((mainBlock.size() % 32) == 0);
        for (std::size_t i = 0; i < mainBlock.size(); i += 32) {
            __m256i mainVec = _mm256_loadu_si256(reinterpret_cast<const __m256i*> (&mainBlock[i]));
            __m256i sideVec = _mm256_loadu_si256(reinterpret_cast<const __m256i*> (&sideBlock[i]));
            mainVec = _mm256_or_si256(mainVec, sideVec);
            _mm256_storeu_si256(reinterpret_cast<__m256i*> (&mainBlock[i]), mainVec);
        }
    }
}

// Change namespace
namespace EndpointConversion {
    /**
     * @brief Get amount of bytes needed to hold range of primes.
     *
     * @param lo    lower inclusive bound.
     * @param hi    upper inclusive bound.
     * @return      Smallest block to fix the range between two primes.
     */
    std::size_t blockSize(std::uint64_t lo, std::uint64_t hi) {
        return FastMath::fastDivideBy30(hi) - FastMath::fastDivideBy30(lo);
    }


    /**
     * @brief Resize vector to fit prime range.
     *
     * @param primesIn  Span of numbers holding primes.
     * @param primesOut Vector of bytes to resize.
     * @assumption      primesIn size > 1
     */
    void adjustBlockSize(const std::span<const std::uint64_t> primesIn, std::vector<std::uint8_t> primesOut) {
        primesOut.resize(blockSize(primesIn.front(), primesIn.back()));
    }

    void mergeSpans(std::span<std::uint8_t> mainBlock, std::span<std::uint8_t> sideBlock) {
        bitwise_or_assign_simd(mainBlock, sideBlock);
    }

    /**
     * @brief compress primes
     * Given list of existing primes compress them.
     *
     * @param primesIn  Span of primes in 8 byte form.
     * @param primesOut List of bytes representing the compressed primes.
     *
     * @optimization_1 change vector type to array and have static size.
     * @optimization_2 change inner function calls to / and % right now from my ad hoc profiling
     *  the function call variants are fast but consistent and the / % is sometimes a bit faster
     *  and sometimes was a bit slower. Was ad hoc because not tested on this program just raw
     *  speed. The calls were consistent though so will use them until this is a bottle neck.
     * @assumption      primesOut has been resized properly.
     */
    void compressBlock(
            const std::span<const std::uint64_t> primesIn, 
            const std::span<std::uint8_t> primesOut) {
        std::fill(primesOut.begin(), primesOut.end(), 0);
        for(const auto& prime: primesIn)
            primesOut[FastMath::fastDivideBy30(prime) % primesOut.size()] |= ProjectConstants::offset_to_mask[FastMath::fastModBy30(prime)];
    }
}
