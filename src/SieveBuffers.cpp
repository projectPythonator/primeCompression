#include "header/SieveBuffers.hpp"

namespace Sieves {
    void mergeSieveSection(std::size_t startIndex, std::size_t endIndex) {
        for (std::size_t i = startIndex; i < endIndex; i++) {
            single_thread_sieve[i] &= (
                multi_thread_sieve[0][i] &
                multi_thread_sieve[1][i] &
                multi_thread_sieve[2][i] &
                multi_thread_sieve[3][i] &
                multi_thread_sieve[4][i] &
                multi_thread_sieve[5][i] &
                multi_thread_sieve[6][i] &
                multi_thread_sieve[7][i]);
        }
    }
}
