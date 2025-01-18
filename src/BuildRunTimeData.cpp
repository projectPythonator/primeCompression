#include "header/BuildRunTimeData.hpp"

namespace {
    void returnMemory(std::vector<std::uint8_t> &obj) {
        obj.clear();
    }
}

// TODO update namespace name
// TODO change const char * to string or something
// TODO figure out compressed primes typing
namespace InitData {
    void prepLevelChange(bool isCompress, std::size_t rbxLevel) {
        std::vector<std::uint8_t> tmpIn;
        std::vector<std::uint8_t> tmpOut;
        CompressionLevelConversion::adjustResultBufferSize(tmpIn, tmpOut, isCompress, rbxLevel);
        std::size_t adjustedSize = std::max(tmpIn.size(), tmpOut.size());
        returnMemory(tmpIn);
        returnMemory(tmpOut);
        std::vector<std::uint8_t> tmpVec(adjustedSize, 0);
        CompressionLevelConversion::adjustDATContainers(isCompress, rbxLevel);
        SieveSegment::sieveSegment(std::span<std::uint8_t>(tmpVec.begin(), tmpVec.size()), rbxLevel);
        CompressionLevelConversion::fillDATContainers(std::span<std::uint8_t>(tmpVec), isCompress);
        returnMemory(tmpVec);
    }

    void initForPrimesToBlocks(const std::span<char> inName, const std::span<char> outName) {
        ProjectIO::setFileForProgram(inName, ProjectIO::FileModeCode::inputText);
        ProjectIO::setFileForProgram(outName, ProjectIO::FileModeCode::outputBinary);
    }

    void initForBlocksToBlocksHigher(
            const std::span<char> inName , const std::span<char> outName, std::size_t newLevel) {

        ProjectIO::setFileForProgram(inName, ProjectIO::FileModeCode::inputBinary);
        ProjectIO::setFileForProgram(outName, ProjectIO::FileModeCode::outputBinary);
        prepLevelChange(true, newLevel);
    }

    void initForBlocksToBlocksLower(
            const std::span<char> inName , const std::span<char> outName, std::size_t newLevel) {
        ProjectIO::setFileForProgram(inName, ProjectIO::FileModeCode::inputBinary);
        ProjectIO::setFileForProgram(outName, ProjectIO::FileModeCode::outputBinary);
        prepLevelChange(false, newLevel);
    }

    void initForBlocksToPrimes(const std::span<char> inName , const std::span<char> outName) {
        ProjectIO::setFileForProgram(inName, ProjectIO::FileModeCode::inputBinary);
        ProjectIO::setFileForProgram(outName, ProjectIO::FileModeCode::outputText);
    }

    void initProgramData(
            const std::span<char> inName , const std::span<char> outName, 
            std::size_t level, std::size_t option) {
        switch (option) {
            case 0u: initForPrimesToBlocks(inName, outName); break;
            case 1u: initForBlocksToBlocksHigher(inName, outName, level); break;
            case 2u: initForBlocksToBlocksLower(inName, outName, level); break;
            case 3u: initForBlocksToPrimes(inName, outName); break;
            default: perror("option not found");
        }
    }
}
