#include "header/HandleMetaData.hpp"

namespace {
    constexpr std::size_t meta_data_block_size = 1 << 16;
    constexpr std::size_t max_compression_level = 6u;

    constexpr std::size_t level_index = 0u;
    constexpr std::size_t start_index = 1u;
    constexpr std::size_t size_index  = 2u;
}

namespace MetaDataInfo {
    MetaData::MetaData(
            const std::span<const char> newName, 
            std::uint64_t newStart, 
            std::uint64_t newLevel) {
        assert(newLevel <= max_compression_level);
        assert(newName.size() <= FILENAME_MAX);
        fileName = std::string(newName.data(), newName.size());
        startPrime = newStart;
        compressionLevel = newLevel;
    }

    void MetaData::writeMetaData() {
        std::array<std::uint64_t, 4> numberData = {compressionLevel, startPrime, fileName.size(), 0};
        std::vector<std::uint8_t> fileNameData(meta_data_block_size - 32u, 0);
        for (std::size_t i = 0; i < fileName.size(); i++)
            fileNameData[i] = (std::uint8_t)fileName[i];

        ProjectIO::writeBlockOfBinary(std::span(numberData));
        ProjectIO::writeBlockOfBytes(std::span(fileNameData));
    }

    void MetaData::readMetaData() {
        std::array<std::uint64_t, 4> numberData = {0, 0, 0, 0};
        std::vector<std::uint8_t> fileNameData(meta_data_block_size - 32u, 0);

        std::size_t readResult1 = ProjectIO::readBlockOfBinary(std::span(numberData));
        std::size_t readResult2 = ProjectIO::readBlockOfBytes(std::span(fileNameData));
        assert(readResult1 == numberData.size());
        assert(readResult2 == fileNameData.size());

        compressionLevel            = numberData[level_index]; 
        startPrime                  = numberData[start_index]; 
        std::size_t fileNameSize    = numberData[size_index];

        assert(compressionLevel <= max_compression_level);
        assert(fileNameSize <= FILENAME_MAX);

        for (std::size_t i = 0; i < fileName.size(); i++)
            fileName += (char)fileNameData[i];
    }
}
