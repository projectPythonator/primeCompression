#ifndef PRIMES_TO_RB5_HPP
#define PRIMES_TO_RB5_HPP

#include "ContainerIncludes.hpp"
#include "FastMath.hpp"
#include "IntegralIncludes.hpp"
#include "ProjectConstants.hpp"
#include "UtilityIncludes.hpp"
#include "TestingIncludes.hpp"

namespace EndpointConversion {
    /**
     * @brief Call to find out how many bytes you need to compress primes in rb5.
     *
     * @param lo    lower inclusive bound.
     * @param hi    upper inclusive bound.
     * @return      Smallest block to fix the range between two primes.
     */
    std::size_t blockSize(std::uint64_t, std::uint64_t);

    /**
     * @brief Call to adjust how many bytes your vector has based on amount needed to compress primes in rb5.
     *
     * @param primesIn  Span of numbers holding primes.
     * @param primesOut Vector of bytes to resize.
     * @assumption      primesIn size > 1
     */
    void adjustBlockSize(const std::span<const std::uint64_t>, std::vector<std::uint8_t>);


    class ToRB5 {
        private:
            std::span<std::uint8_t> blockSpan;
            std::vector<std::uint8_t> block;
        public: 
            std::span<std::uint8_t> getPrintSpan(std::size_t printSize) { 
                return blockSpan.first(printSize); 
            }

            std::span<std::uint8_t> getSubSpan(std::size_t spanStart, std::size_t spanSize) { 
                return blockSpan.subspan(spanStart, spanSize);
            }

            void resetSpan() {
                blockSpan = std::span(block.begin(), block.size());
            }

            void resizeData(std::size_t newSize) {
                block.assign(newSize, 0u);
                resetSpan();
            }


            /**
             * @brief Call to compress a block of prime numbers into bytes.
             *
             * @param primesIn  Span of primes in 8 byte form.
             * @param primesOut Span of bytes representing the compressed primes.
             *
             * @assumption      primesOut has been resized properly.
             */
            void compressBlock(const std::span<const std::uint64_t>, const std::span<std::uint8_t>);
    };

}

#endif
