#ifndef CHANGE_COMPRESSION_LEVEL_HPP
#define CHANGE_COMPRESSION_LEVEL_HPP

#include "ContainerIncludes.hpp"
#include "FastMath.hpp"
#include "IntegralTypeIncludes.hpp"
#include "ProjectConstants.hpp"

namespace CompressionLevelConversion {
    void adjustDATContainers(bool, std::size_t);
    std::size_t adjustResultBufferSize(std::vector<std::uint8_t>, std::vector<std::uint8_t>, bool, std::size_t);

    void fillDATContainers(const std::span<std::uint8_t>, bool);
    void applyHigherCompressionLevel(const std::span<std::uint8_t>, std::span<std::uint8_t>);
    void normalizeHigherCompression(const std::span<std::uint8_t>, std::span<std::uint8_t>);
}

#endif
