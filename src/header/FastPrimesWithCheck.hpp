// file used for sieving medium primes
//
#include "ByteMasks.hpp"
#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"

// TODO fix missing includes I am missing 1-3
// TODO fix typing of pointer to span
// TODO turn into class methods
namespace SieveCompress {

    void crossOff_1(uint8_t *,  std::size_t, std::size_t, std::size_t);
    void crossOff_7(uint8_t *,  std::size_t, std::size_t, std::size_t);
    void crossOff_11(uint8_t *, std::size_t, std::size_t, std::size_t);
    void crossOff_13(uint8_t *, std::size_t, std::size_t, std::size_t);
    void crossOff_17(uint8_t *, std::size_t, std::size_t, std::size_t);
    void crossOff_19(uint8_t *, std::size_t, std::size_t, std::size_t);
    void crossOff_23(uint8_t *, std::size_t, std::size_t, std::size_t);
    void crossOff_29(uint8_t *, std::size_t, std::size_t, std::size_t);
} 

