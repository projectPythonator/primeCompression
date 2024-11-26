// file used for sieving medium primes
//
#include "ByteMasks.hpp"
#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"

// TODO fix missing includes I am missing 1-3
// TODO fix typing of pointer to span
// TODO turn into class methods
namespace SieveCompress {

    void crossOff_1(std::span<uint8_t>, std::size_t, std::size_t);
    void crossOff_7(std::span<uint8_t>, std::size_t, std::size_t);
    void crossOff_11(std::span<uint8_t>, std::size_t, std::size_t);
    void crossOff_13(std::span<uint8_t>, std::size_t, std::size_t);
    void crossOff_17(std::span<uint8_t>, std::size_t, std::size_t);
    void crossOff_19(std::span<uint8_t>, std::size_t, std::size_t);
    void crossOff_23(std::span<uint8_t>, std::size_t, std::size_t);
    void crossOff_29(std::span<uint8_t>, std::size_t, std::size_t);
} 

