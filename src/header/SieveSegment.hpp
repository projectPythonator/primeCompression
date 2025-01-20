#ifndef SIEVE_SEGMENT_HPP
#define SIEVE_SEGMENT_HPP

#include "ContainerIncludes.hpp"
#include "FastMath.hpp"
#include "IntegralTypeIncludes.hpp"
#include "ProjectConstants.hpp"

namespace SieveSegment {
    void sieveSegment(std::span<std::uint8_t>, std::size_t);
}

#endif
