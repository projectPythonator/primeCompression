#ifndef CHANGE_LEVEL_LOWER_HPP
#define CHANGE_LEVEL_LOWER_HPP

#include "ContainerIncludes.hpp"
#include "FastMath.hpp"
#include "IntegralTypeIncludes.hpp"
#include "ProjectConstants.hpp"

namespace DecreaseLevel {
    /**
     * @brief Call to resize your buffers and resize namespace buffers
     *
     * @param bufferIn  Buffer for the current level of compression.
     * @param bufferOut Buffer for the higher level of compression.
     * @param rbxLevel  Number indicating the level you want to decrease to.
     *
     * @assumption      Level is less than 6.
     */
    void initData(std::vector<std::uint8_t>, std::vector<std::uint8_t>, std::size_t);

    /**
     * @brief Call with rb5 buffer to fill dat buffers.
     *
     * @param rb5Block  Block of sieved rb5 format bytes, for the level you desire.
     *
     * @assumption      dat buffers are properly resized before hand.
     */
    void fillDATContainers(const std::span<const std::uint8_t>);

    /**
     * @brief Call to decompress higher level to rb5.
     *
     * @param rbxBlock  Block of high compressed primes.
     * @param rb5Block  Block of rb5 to hold the lower compression.
     *
     * @assumption      Both blocks are formatted and sized properly.
     * @assumption      dat is filled and sized properly.
     */
    void CompressLower(const std::span<const std::uint8_t>, const std::span<std::uint8_t>);
}
#endif
