#ifndef RB5_TO_PRIMES_HPP
#define RB5_TO_PRIMES_HPP

#include "ContainerIncludes.hpp"
#include "FastMath.hpp"
#include "IntegralIncludes.hpp"
#include "ProjectConstants.hpp"
#include "UtilityIncludes.hpp"
#include "TestingIncludes.hpp"

namespace EndpointConversion {

    /**
     * @brief Call to find how many primes a block of bytes has.
     *
     * @param block Span of compressed primes.
     * @return      Number of bits set.
     */
    std::size_t blockPopcount(std::span<std::uint8_t>);

    /**
     * @brief Call to extra prime number from compressed byte.
     *
     * @param block is the offset which our prime is at
     * @param mask holds the next prime in byte form
     * @return 8 byte prime number
     */
    std::uint64_t extractNextPrime(std::uint64_t, std::uint8_t);

    class RB5ToPrimes {
        private:
            std::span<std::uint64_t> primeSpan;
            std::vector<std::uint64_t> primes;
        public: 
            std::span<std::uint64_t> getPrintSpan(std::size_t printSize) { 
                return primeSpan.first(printSize); 
            }

            std::span<std::uint64_t> getSubSpan(std::size_t spanStart, std::size_t spanSize) { 
                return primeSpan.subspan(spanStart, spanSize);
            }

            void resetSpan() {
                primeSpan = std::span(primes.begin(), primes.size());
            }

            void resizeData(std::size_t newSize) {
                primes.assign(newSize, 0u);
                resetSpan();
            }


            /**
             * @brief Call to extract a list of primes from a block of bytes.
             *
             * @param primesIn  Span of bytes representing the compressed primes.
             * @param primesOut Span of 8 byte numbers to store the primes in.
             * @param offset    The starting point that our compressed primes start at.
             *
             * @assumption      primesOut has been resized properly.
             */
            void decompressBlock(const std::span<const std::uint8_t>, const std::span<std::uint64_t>, std::uint64_t);
    };

}

#endif
