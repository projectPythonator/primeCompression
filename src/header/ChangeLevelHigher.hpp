#ifndef CHANGE_LEVEL_HIGHER_HPP
#define CHANGE_LEVEL_HIGHER_HPP

#include "ContainerIncludes.hpp"
#include "FastMath.hpp"
#include "IntegralIncludes.hpp"
#include "ProjectConstants.hpp"
#include "TestingIncludes.hpp"
    
namespace IncreaseLevel {

    /**
     * @brief Call to resize your buffers and resize namespace buffers
     *
     * @param bufferIn  Buffer for the current level of compression.
     * @param bufferOut Buffer for the higher level of compression.
     * @param rbxLevel  Number indicating the level you want to increase to.
     *
     * @assumption      Level is less than 6. (checked)
     */
    void initData(std::vector<std::uint8_t>, std::vector<std::uint8_t>, std::size_t);

    /**
     * @brief Call with rb5 buffer to fill dat buffers.
     *
     * @param rb5Block  Block of sieved rb5 format bytes, for the level you desire.
     *
     * @assumption      dat buffers are properly resized before hand. (not checked)
     */
    void fillDATContainers(const std::span<const std::uint8_t>);

    /**
     * @brief Call to convert lower compression to higher compression.
     *
     * @param rb5Block  Block of rb5 compressed bytes.
     * @param rbxBlock  Block that will hold the resulting compression.
     *
     * @assumption      Both blocks are formatted and sized properly.   (not checked)
     * @assumption      dat is filled and sized properly.               (not checked)
     */
    void CompressHigher(const std::span<const std::uint8_t>, std::span<std::uint8_t>);
}

#endif
