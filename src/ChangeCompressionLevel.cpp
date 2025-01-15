#include "header/ChangeCompressionLevel.hpp"

// TODO make class out of this 
namespace {
    std::vector<std::size_t> dat_lookup;
    std::vector<std::size_t> dat_byte_positions;
    std::vector<std::uint8_t> dat_masks;
    constexpr std::size_t rb5_level = 1;
    constexpr std::size_t max_compression_level = 6;

    void resetDATmemory() {
        dat_byte_positions.clear();
        dat_lookup.clear();
        dat_masks.clear();
        dat_byte_positions.shrink_to_fit();
        dat_lookup.shrink_to_fit();
        dat_masks.shrink_to_fit();
    }

    std::size_t getLookupIndex(std::size_t block, std::uint8_t mask) {
        return 8 * block + std::countr_zero(mask); 
    }
}

// TODO make class out of this 
namespace CompressionLevelConversion {
    
    void adjustDATContainers(bool isCompress, std::size_t rbxLevel) {
        resetDATmemory();
        if (isCompress) {
            dat_lookup.assign(
                    (ProjectConstants::primorial_values[rbxLevel] / 
                     ProjectConstants::primorial_values[rb5_level]) * 
                    ProjectConstants::phi_values[rb5_level], 0);
        }
        dat_byte_positions.assign(ProjectConstants::phi_values[rbxLevel], 0);
        dat_masks.assign(ProjectConstants::phi_values[rbxLevel], 0);
    }

    void adjustResultBufferSize(std::vector<std::uint8_t> bufferIn, 
                                std::vector<std::uint8_t> bufferOut, 
                                bool isCompress, std::size_t rbxLevel) {
        if (!(rb5_level < rbxLevel && rbxLevel < max_compression_level))
            return;
        std::size_t rb5BlockSize = 
            ceil(ProjectConstants::phi_values[rbxLevel] / ProjectConstants::phi_values[rb5_level]);
        std::size_t rbxBlockSize = 
            ProjectConstants::primorial_values[rbxLevel] / ProjectConstants::primorial_values[rb5_level];
        std::size_t bufferInSize = (isCompress)? rbxBlockSize: rb5BlockSize; 
        std::size_t bufferOutSize = (isCompress)? rb5BlockSize: rbxBlockSize; 
        bufferIn.clear();
        bufferOut.clear();
        bufferIn.shrink_to_fit();
        bufferOut.shrink_to_fit();
        bufferIn.assign(bufferInSize, 0);
        bufferOut.assign(bufferOutSize, 0);
    }


    void fillDATContainers(const std::span<std::uint8_t> rb5Block, bool isCompress) {
        std::size_t rbXIndex = 0;
        std::uint8_t rotatingMask = 1;
        for (std::size_t block = 0; block < rb5Block.size(); block++)
            if (rb5Block[block]) 
                for (std::uint8_t mask = rb5Block[block]; mask; mask ^= (-mask & mask)) {
                    if (isCompress) 
                        dat_lookup[getLookupIndex(block, mask)] = rbXIndex;
                    dat_byte_positions[rbXIndex] = (isCompress)? rbXIndex/8  : block; 
                    dat_masks[rbXIndex]          = (isCompress)? rotatingMask: (-mask & mask);
                    rotatingMask = std::rotl(rotatingMask, 1);
                    rbXIndex++;
                }
    }

    void applyHigherCompressionLevel(const std::span<std::uint8_t> rb5Block, std::span<std::uint8_t> rbxBlock) {
         for (std::size_t block = 0; block < rb5Block.size(); block++)
            if (rb5Block[block]) 
                for (std::uint8_t mask = rb5Block[block]; mask; mask ^= (-mask & mask)) {
                    std::size_t lookupIndex = dat_lookup[getLookupIndex(block, mask)]; 
                    rbxBlock[dat_byte_positions[lookupIndex]] |= dat_masks[lookupIndex];
                }
    }

    void normalizeHigherCompression(const std::span<std::uint8_t> rbxBlock, std::span<std::uint8_t> rb5Block) {
        for (std::size_t block = 0; block < rbxBlock.size(); block++)
            if (rbxBlock[block]) 
                for (std::uint8_t mask = rbxBlock[block]; mask; mask ^= (-mask & mask)) {
                    std::size_t lookupIndex = getLookupIndex(block, mask); 
                    rb5Block[dat_byte_positions[lookupIndex]] |= dat_masks[lookupIndex];
                }
    }
}
