#include "header/BuildRunTimeData.hpp"

namespace {
    void returnMemory(std::vector<std::uint8_t> &obj) {
        tmpIn.clear();
        tmpOut.clear();
    }
}

// TODO update namespace name
// TODO change const char * to string or something
// TODO figure out compressed primes typing
namespace InitData {
    void prepLevelChange(bool isCompress, std::size_t rbxlevel) {
        std::vector<std::uint8_t> tmpIn;
        std::vector<std::uint8_t> tmpOut;
        CompressionLevelConversion::adjustResultBufferSize(tmpIn, tmpOut, isCompress, rbxLevel);
        std::size_t adjustedSize = std::max(tmpIn.size(): tmpOut.size());
        returnMemory(tmpIn);
        returnMemory(tmpOut);
        std::vector<std::uint8_t> tmpVec(adjustedSize, 0);
        CompressionLevelConversion::adjustDATContainers(isCompress, rbxLevel);
        SieveSegment::sieveSegment(std::span<std::uint8_t>(tmpVec), rbxLevel);
        CompressionLevelConversion::fillDATContainers(std::span<std::uint8_t>(tmpVec), isCompress);
        returnMemory(tmpVec);
    }

    void initForPrimesToBlocks(const char *inName, const char *outName) {
        FileIO::openInStreamInTextAndSetBufSize(inName);
        FileIO::openOutStreamInBinaryAndSetBufSize(outName);
    }

    void initForBlocksToBlocksHigher(
            const char *inName , const char *outName, std::size_t newLevel) {
        FileIO::openInStreamInBinaryAndSetBufSize(inName);
        FileIO::openOutStreamInBinaryAndSetBufSize(outName);
        prepLevelChange(true, newLevel);
    }

    void initForBlocksToBlocksLower(
            const char *inName , const char *outName, std::size_t newLevel) {
        FileIO::openInStreamInBinaryAndSetBufSize(inName);
        FileIO::openOutStreamInBinaryAndSetBufSize(outName);
        prepLevelChange(false, newLevel);
    }

    void initForPrimesToBlocks(const char *inName, const char *outName) {
        FileIO::openInStreamInBinaryAndSetBufSize(inName);
        FileIO::openOutStreamInTextAndSetBufSize(outName);
    }

    void initProgramData(
            const char *inName, const char *outName, 
            std::size_t level, std::size_t threads, std::size_t option) {
        switch (option) {
            case 0: initForPrimesToBlocks(inName, outName); break;
            case 1: initForBlocksToBlocksHigher(inName, outName); break;
            case 2: initForBlocksToBlocksLower(inName, outName); break;
            case 3: initForPrimesToBlocks(inName, outName); break;
            default: perror("option not found");
        }
    }
}
