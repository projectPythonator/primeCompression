#include "header/ChangeLevelHigher.hpp"
#include <cassert>

namespace {
    std::vector<std::size_t> dat_lookup;
    std::vector<std::size_t> dat_byte_positions;
    std::vector<std::uint8_t> dat_masks;

    constexpr std::size_t rb5_level = 1;
    constexpr std::size_t max_compression_level = 6;

    std::size_t getLookupIndex(std::size_t block, std::uint8_t mask) {
        return 8 * block + std::countr_zero(mask); 
    }

    void adjustDATContainers(std::size_t rbxLevel) {
        std::size_t rb5Phi = ProjectConstants::phi_values[rb5_level];
        std::size_t rbxPhi = ProjectConstants::phi_values[rbxLevel];
        std::size_t rb5Primorial = ProjectConstants::primorial_values[rb5_level];
        std::size_t rbxPrimorial = ProjectConstants::primorial_values[rbxLevel];

        dat_lookup.resize(((rbxPrimorial / rb5Primorial) * rb5Phi), 0);
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

        std::size_t bufferInSize = rbxPrimorial / rb5Primorial;
        std::size_t bufferOutSize = ceil(rbxPhi / rb5Phi);
        bufferIn.resize(bufferInSize, 0);
        bufferOut.resize(bufferOutSize, 0);
    }
}

// TODO add check on rb5Block fill 
namespace IncreaseLevel {
    /**
     * @brief Will Resize your buffers and size the source file buffers
     *
     * @param bufferIn  Buffer for the current level of compression.
     * @param bufferOut Buffer for the higher level of compression.
     * @param rbxLevel  Number indicating the level you want to increase to.
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
     * @brief fill dat containers so you can convert to a higher level.
     *
     * @param rb5Block  Block of sieved rb5 format bytes, for the level you desire.
     *
     * @assumption      dat buffers are properly resized before hand.
     */
    void fillDATContainers(const std::span<const std::uint8_t> rb5Block) {
        std::size_t rbXIndex = 0;
        std::uint8_t rotatingMask = 1;
        for (std::size_t block = 0; block < rb5Block.size(); block++)
            if (rb5Block[block]) 
                for (std::uint8_t mask = rb5Block[block]; mask; mask ^= (-mask & mask)) {
                    dat_lookup[getLookupIndex(block, mask)] = rbXIndex;
                    dat_byte_positions[rbXIndex]            = rbXIndex/8; 
                    dat_masks[rbXIndex]                     = rotatingMask;
                    rotatingMask = std::rotl(rotatingMask, 1);
                    rbXIndex++;
                }
    }

    /**
     * @brief Apply a higher compression to a buffer given rb5 buffer.
     *
     * @param rb5Block  Block of rb5 compressed bytes.
     * @param rbxBlock  Block that will hold the resulting compression.
     *
     * @assumption      Both blocks are formatted and sized properly.
     * @assumption      dat is filled and sized properly.
     */
    void CompressHigher(const std::span<const std::uint8_t> rb5Block, std::span<std::uint8_t> rbxBlock) {
         for (std::size_t block = 0; block < rb5Block.size(); block++)
            if (rb5Block[block]) 
                for (std::uint8_t mask = rb5Block[block]; mask; mask ^= (-mask & mask)) {
                    std::size_t lookupIndex = dat_lookup[getLookupIndex(block, mask)]; 
                    rbxBlock[dat_byte_positions[lookupIndex]] |= dat_masks[lookupIndex];
                }
    }
}
