#include "IntegralTypeIncludes.hpp"
#include "ContainerIncludes.hpp"
#include "PrimeInfoRecords.hpp"


// TODO update namespace name
// TODO change const char * to string or something
// TODO figure out compressed primes typing
namespace PlaceHolder {

    // place holder only since no longer doing jumps
    // void fillJumpsInfo(const std::span<uint8_t>);
    uint64_t calculateStartByte(uint32_t, uint8_t);
    void fillByteInfo(const std::span<uint8_t>);
    void fillKvalueInfo(const std::span<uint8_t>);
    void fillMaskPosInfo(const std::span<uint8_t>);
    void fillSqrtPrimesInfo(const std::span<uint8_t>);
    void assignVectorSpace();
    void fillSqrtPrimesBoundValues();
    void readCompressedSqrtPrimes(std::span<uint8_t>);
    void precompute(const char *);

}
