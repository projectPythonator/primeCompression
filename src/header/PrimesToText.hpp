#ifndef PRIMES_TO_TEXT_HPP
#define PRIMES_TO_TEXT_HPP

#include "ContainerIncludes.hpp"
#include "IntegralIncludes.hpp"
#include "TestingIncludes.hpp"
#include "UtilityIncludes.hpp"


namespace EndPointConversions {
    /**
     * @brief convert number n to string and store it in the span
     *
     * @assumption_1    no prime is 0
     */
    void addNextNumberBase10_XXd(std::span<std::uint8_t>, std::uint64_t);
    void addNextNumberBase10(std::span<std::uint8_t>, std::uint64_t);

    class ToText {
        private:
            std::span<std::uint8_t> numberSpan;
            std::vector<std::uint8_t> numbers;
        public: // use protected?

            std::span<std::uint8_t> getPrintSpan(std::size_t printSize) { 
                return numberSpan.first(printSize); 
            }

            std::span<std::uint8_t> getSubSpan(std::size_t spanStart, std::size_t spanSize) { 
                return numberSpan.subspan(spanStart, spanSize);
            }

            void resetSpan() {
                numberSpan = std::span(numbers.begin(), numbers.size());
            }

            void resizeData(std::size_t newSize) {
                numbers.assign(newSize, 0u);
                resetSpan();
            }

            /**
             * @brief convert list of numbers into a buffer
             * call with the params and you will recieve a buffer of text in numbers
             *
             * @param primes    a list of primes to convert
             * @param numbers   buffer to hold the output
             * @return  end index of the buffer
             *
             * @assumption_1    numbers is big enough to hold primes
             * @assumption_1    no prime is 0
             */
            std::size_t convertPrimesBlock(std::span<const std::uint64_t>, const std::span<std::uint8_t>);
    };
}
#endif
