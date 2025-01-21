#ifndef CHANGE_LEVEL_HIGHER_HPP
#define CHANGE_LEVEL_HIGHER_HPP

#include "ContainerIncludes.hpp"
#include "FastMath.hpp"
#include "IntegralTypeIncludes.hpp"
#include "ProjectConstants.hpp"
    
namespace IncreaseLevel {
    void initData(std::vector<std::uint8_t>, std::vector<std::uint8_t>, std::size_t);

    void fillDATContainers(const std::span<const std::uint8_t>);

    void CompressHigher(const std::span<const std::uint8_t>, std::span<std::uint8_t>);
}

#endif
