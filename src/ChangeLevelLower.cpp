#include "header/ChangeLevelLower.hpp"
#include <cassert>

namespace {
    std::vector<std::size_t> dat_byte_positions;
    std::vector<std::uint8_t> dat_masks;

    constexpr std::size_t rb5_level = 1;
    constexpr std::size_t max_compression_level = 6;

    std::size_t getLookupIndex(std::size_t block, std::uint8_t mask) {
        return 8 * block + std::countr_zero(mask); 
    }

    void adjustDATContainers(std::size_t rbxLevel) {
        std::size_t rbxPhi = ProjectConstants::phi_values[rbxLevel];
        dat_byte_positions.resize(rbxPhi, 0);
        dat_masks.resize(rbxPhi, 0);
    }

    void adjustResultBufferSize(
            std::vector<std::uint8_t> bufferIn, 
            std::vector<std::uint8_t> bufferOut, 
            std::size_t rbxLevel) {
        std::size_t rb5Phi = ProjectConstants::phi_values[rb5_level];
        std::size_t rbxPhi = ProjectConstants::phi_values[rbxLevel];
        std::size_t rb5Primorial = ProjectConstants::primorial_values[rb5_level];
        std::size_t rbxPrimorial = ProjectConstants::primorial_values[rbxLevel];

        std::size_t bufferInSize = ceil(rbxPhi / rb5Phi);
        std::size_t bufferOutSize = rbxPrimorial / rb5Primorial;
        bufferIn.resize(bufferInSize, 0);
        bufferOut.resize(bufferOutSize, 0);
    }
}

namespace DecreaseLevel {
    /**
     * @brief Will Resize your buffers and size the source file buffers
     *
     * @param bufferIn  Buffer for the current level of compression.
     * @param bufferOut Buffer for the higher level of compression.
     * @param rbxLevel  Number indicating the level you want to decrease to.
     *
     * @assumption      Level is less than 6.
     */
    void initData(
            std::vector<std::uint8_t> bufferIn, 
            std::vector<std::uint8_t> bufferOut, 
            std::size_t rbxLevel) {
        assert(rbxLevel < max_compression_level);
        adjustDATContainers(rbxLevel);
        adjustResultBufferSize(bufferIn, bufferOut, rbxLevel);
    }

    /**
     * @brief fill dat containers so you can decompress.
     *
     * @param rb5Block  Block of sieved rb5 format bytes, for the level you desire.
     *
     * @assumption      dat buffers are properly resized before hand.
     */
    void fillDATContainers(const std::span<const std::uint8_t> rb5Block) {
        std::size_t rbXIndex = 0;
        for (std::size_t block = 0; block < rb5Block.size(); block++)
            if (rb5Block[block]) 
                for (std::uint8_t mask = rb5Block[block]; mask; mask ^= (-mask & mask)) {
                    dat_byte_positions[rbXIndex] = block; 
                    dat_masks[rbXIndex]          = (-mask & mask);
                    rbXIndex++;
                }
    }

    /**
     * @brief Lower compression of higher level down to rb5
     *
     * @param rbxBlock  Block of high compressed primes.
     * @param rb5Block  Block of rb5 to hold the lower compression.
     *
     * @assumption      Both blocks are formatted and sized properly.
     * @assumption      dat is filled and sized properly.
     */
    void CompressLower(const std::span<const std::uint8_t> rbxBlock, const std::span<std::uint8_t> rb5Block) {
        for (std::size_t block = 0; block < rbxBlock.size(); block++)
            if (rbxBlock[block]) 
                for (std::uint8_t mask = rbxBlock[block]; mask; mask ^= (-mask & mask)) {
                    std::size_t lookupIndex = getLookupIndex(block, mask); 
                    rb5Block[dat_byte_positions[lookupIndex]] |= dat_masks[lookupIndex];
                }
    }
}
