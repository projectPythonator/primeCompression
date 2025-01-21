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
    void initData(
            std::vector<std::uint8_t> bufferIn, 
            std::vector<std::uint8_t> bufferOut, 
            std::size_t rbxLevel) {
        assert(rbxLevel < max_compression_level);
        adjustDATContainers(rbxLevel);
        adjustResultBufferSize(bufferIn, bufferOut, rbxLevel);
    }

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

    void CompressLower(const std::span<const std::uint8_t> rbxBlock, const std::span<std::uint8_t> rb5Block) {
        for (std::size_t block = 0; block < rbxBlock.size(); block++)
            if (rbxBlock[block]) 
                for (std::uint8_t mask = rbxBlock[block]; mask; mask ^= (-mask & mask)) {
                    std::size_t lookupIndex = getLookupIndex(block, mask); 
                    rb5Block[dat_byte_positions[lookupIndex]] |= dat_masks[lookupIndex];
                }
    }
}
