#ifndef RBX_CONSTANTS_HPP
#define RBX_CONSTANTS_HPP

#include "ContainerIncludes.hpp" // for array
#include "IntegralTypeIncludes.hpp"

// TODO decide on correct typing of the values
// TODO use std::array or our::array instead of native
namespace RBXInfo {
    constexpr uint64_t rbx_primorials[10];  // might need better typing
    constexpr uint64_t rbx_phis[10];        // might need better typing
    constexpr uint8_t rb5_primorial = 30u;  // might need better type
    constexpr uint8_t rb5_phi = 8u;         // might need better type
}

#endif
