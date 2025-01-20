#include "header/FastMath.hpp"
#include <cassert>


// TODO add documentation
namespace {
    constexpr std::uint64_t pi_fp = 0x517cc1b727220a95ULL;      // pi inverse fixed point 
    constexpr std::uint64_t prime_fp = 8579638605549648317ULL;  // random big prime number
    constexpr unsigned left_shift = 6u;
    constexpr unsigned right_shift = 2u;

    // following taken from SO: https://stackoverflow.com/a/57556517 edited 
    constexpr std::uint64_t p_value = 0x5555555555555555ULL;    // pattern of alternating 0 and 1
    constexpr std::uint64_t c_value = 17316035218449499591ULL;  // random uneven integer constant
    constexpr unsigned xor_shift_amount = 32;                   // wsa changed from int to unsigned
                                                                // as per c++ core guidelines

    std::uint64_t xorShift(const std::uint64_t& n, unsigned i){
        return n^(n>>i);
    }

    std::uint64_t xorHash(const std::uint64_t& n){
        return c_value * xorShift(p_value * xorShift(n, xor_shift_amount), xor_shift_amount);
    }
    // taken section over
    
    // boost style hash combine seen ^= hash(value) + const + (seed << 6) + (seed >> 2)
    // edited to conform to c++ core guidelines
    std::uint64_t boostHashCombine(std::uint64_t fixedPoint, std::uint64_t lhs, std::uint64_t rhs) {
        return lhs ^ (xorHash(rhs) + fixedPoint + (lhs << left_shift) + (lhs >> right_shift));
    }
    // boost code over

    // function here to just provide a way to get combined hashes 
    void hashBatch(std::span<const std::uint64_t> values, std::uint64_t &piHash, std::uint64_t &primeHash) {
        std::uint64_t piResult = values[0];
        std::uint64_t primeResult = values[0];
        for (const std::uint64_t &value: values) {
            piResult = boostHashCombine(pi_fp, piResult, value);
            primeResult = boostHashCombine(prime_fp, primeResult, value);
        }
        piHash = piResult;
        primeHash = primeResult;
    }
}

namespace FastMath {
   
    void generate_hashes(const std::span<const std::uint64_t> metaData, std::span<std::uint64_t> hashes) {
        assert(metaData.size() == 5u);
        std::array<std::uint64_t, 5u> metaFor{0};
        std::array<std::uint64_t, 5u> metaRev{0};
        for (std::size_t i = 0; i < metaData.size(); i++) {
            metaFor[i] = metaData[i];
            metaRev[(metaData.size()-i)-1] = metaData[i];
        }
        hashBatch(std::span<const std::uint64_t>(metaFor.begin(), metaFor.size()), hashes[0], hashes[1]);
        hashBatch(std::span<const std::uint64_t>(metaRev.begin(), metaRev.size()), hashes[2], hashes[3]);
    }
}
