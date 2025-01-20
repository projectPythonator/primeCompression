#include "header/FastMath.hpp"

namespace {
    constexpr std::uint32_t golden_ratio_fp = 0x9e3779b9;
    constexpr std::uint64_t pi_fp = 0x517cc1b727220a95ULL;
    constexpr std::uint64_t random_prime_fp = 8579638605549648317ULL;
    constexpr unsigned left_shift = 6u;
    constexpr unsigned right_shift = 2u;

    std::uint32_t golden_hash(std::uint32_t lhs, std::uint32_t rhs) {
        return lhs ^ (rhs + golden_ratio_fp + (lhs << left_shift) + (lhs >> right_shift));
    }
    
    std::uint64_t pi_hash(std::uint64_t lhs, std::uint64_t rhs) {
        return lhs ^ (rhs + pi_fp + (lhs << left_shift) + (lhs >> right_shift));
    }

    std::uint64_t big_prime_hash(std::uint64_t lhs, std::uint64_t rhs) {
        return lhs ^ (rhs + random_prime_fp + (lhs << left_shift) + (lhs >> right_shift));
    }

    void golden_batch(std::span<std::uint64_t> hashes, std::uint64_t value, std::size_t e) {
        std::uint32_t a = (uint32_t)value;
        std::uint32_t b = (uint32_t)std::hash<std::uint64_t>{}(value);
        hashes[0] = golden_hash((uint32_t) hashes[0], a);
        hashes[1] = golden_hash((uint32_t) hashes[1], b);

        hashes[2] = golden_hash((uint32_t) hashes[2], a);
        hashes[2] = golden_hash((uint32_t) hashes[2], b);
        
        hashes[e] = golden_hash((uint32_t) hashes[e], a);
        hashes[e] = golden_hash((uint32_t) hashes[e], b);
    }

    void pi_batch(std::span<std::uint64_t> hashes, std::uint64_t value, std::size_t e) {
        std::uint64_t a = value;
        std::uint64_t b = std::hash<std::uint64_t>{}(value);

        hashes[0] = pi_hash(hashes[0], a);
        hashes[1] = pi_hash(hashes[1], b);

        hashes[2] = pi_hash(hashes[2], a);
        hashes[2] = pi_hash(hashes[2], b);

        hashes[e] = pi_hash(hashes[e], a);
        hashes[e] = pi_hash(hashes[e], b);
    }

    void prime_batch(std::span<std::uint64_t> hashes, std::uint64_t value, std::size_t e) {
        std::uint64_t a = value;
        std::uint64_t b = std::hash<std::uint64_t>{}(value);

        hashes[0] = big_prime_hash(hashes[0], a);
        hashes[1] = big_prime_hash(hashes[1], b);

        hashes[2] = big_prime_hash(hashes[2], a);
        hashes[2] = big_prime_hash(hashes[2], b);

        hashes[e] = big_prime_hash(hashes[e], a);
        hashes[e] = big_prime_hash(hashes[e], b);
    }

}

namespace FastMath {
    void generate_hashes(const std::span<const std::uint64_t> metaData, std::span<std::uint64_t> hashes) {
        for (std::uint64_t value: metaData) {
            hashes[4] = big_prime_hash(hashes[4], value);
            hashes[5] = big_prime_hash(hashes[5], std::hash<std::uint64_t>{}(value));

            hashes[0] = golden_hash((uint32_t) hashes[0], (uint32_t)value);
            hashes[1] = golden_hash((uint32_t) hashes[1], (uint32_t)std::hash<std::uint64_t>{}(value));
            hashes[2] = pi_hash(hashes[2], value);
            hashes[3] = pi_hash(hashes[3], std::hash<std::uint64_t>{}(value));
            hashes[4] = big_prime_hash(hashes[4], value);
            hashes[5] = big_prime_hash(hashes[5], std::hash<std::uint64_t>{}(value));

            hashes[9] = golden_hash((uint32_t) hashes[9], (uint32_t)value);
            hashes[9] = golden_hash((uint32_t) hashes[9], (uint32_t)std::hash<std::uint64_t>{}(value));
            hashes[9] = pi_hash(hashes[9], value);
            hashes[9] = pi_hash(hashes[9], std::hash<std::uint64_t>{}(value));
            hashes[9] = big_prime_hash(hashes[9], value);
            hashes[9] = big_prime_hash(hashes[9], std::hash<std::uint64_t>{}(value));

        }
    }
}
