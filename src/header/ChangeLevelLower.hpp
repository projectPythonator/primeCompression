#ifndef CHANGE_LEVEL_LOWER_HPP
#define CHANGE_LEVEL_LOWER_HPP

#include "ContainerIncludes.hpp"
#include "FastMath.hpp"
#include "IntegralTypeIncludes.hpp"
#include "ProjectConstants.hpp"

namespace DecreaseLevel {
    void initData(std::vector<std::uint8_t>, std::vector<std::uint8_t>, std::size_t);

    void fillDATContainers(const std::span<const std::uint8_t>);

    void CompressLower(const std::span<const std::uint8_t>, const std::span<std::uint8_t>);
}
#endif
