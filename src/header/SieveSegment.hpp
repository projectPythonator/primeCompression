#ifndef SIEVE_SEGMENT_HPP
#define SIEVE_SEGMENT_HPP

#include "ContainerIncludes.hpp"
#include "FastMath.hpp"
#include "IntegralTypeIncludes.hpp"
#include "ProjectConstants.hpp"

namespace SieveSegment {

     /**
     * @brief build the sieve mapping needing for higher level lookup
     * call with params to get the sieve mapping needed to go from rb5 to rbX higher levels and viceversa
     *
     * @param segment   holds bit masks mapping it should confirm in size to primorial_5 / primorial_x
     * @param level     the level to which we need to sieve 
     */
    void sieveSegment(std::span<std::uint8_t>, std::size_t);
}

#endif
