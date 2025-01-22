#include "header/BuildRunTimeData.hpp"

namespace {
    void returnMemory(std::vector<std::uint8_t> &obj) {
        obj.clear();
    }

    void prepLevelChange(bool isCompress, std::size_t rbxLevel) {
        std::vector<std::uint8_t> tmpIn;
        std::vector<std::uint8_t> tmpOut;
        if (isCompress) {
            IncreaseLevel::initData(tmpIn, tmpOut, rbxLevel);
        } else { 
            DecreaseLevel::initData(tmpIn, tmpOut, rbxLevel);
        }
        std::size_t adjustedSize = std::max(tmpIn.size(), tmpOut.size());
        returnMemory(tmpIn);
        returnMemory(tmpOut);
        std::vector<std::uint8_t> tmpVec(adjustedSize, 0);
        std::span<std::uint8_t> tmpVecSpan(tmpVec);
        SieveSegment::sieveSegment(tmpVecSpan, rbxLevel);
        if (isCompress) {
            IncreaseLevel::fillDATContainers(tmpVecSpan);
        } else { 
            DecreaseLevel::fillDATContainers(tmpVecSpan);
        }
    }

    /**
     * @brief Tailored function to set program up for this endpoint.
     *
     * @param inName    String that holds the in file name [stdin default].
     * @param outName   String that holds the out file name [stdout default].
     *
     * @assumption      Files exist.
     */
    void initForPrimesToBlocks(const std::span<char> inName, const std::span<char> outName) {
        ProjectIO::setFileForProgram(inName, ProjectIO::FileModeCode::inputText);
        ProjectIO::setFileForProgram(outName, ProjectIO::FileModeCode::outputBinary);
    }

    /**
     * @brief Tailored function to set program up for this endpoint.
     *
     * @param inName    String that holds the in file name [stdin default].
     * @param outName   String that holds the out file name [stdout default].
     *
     * @assumption      Files exist.
     */
    void initForBlocksToBlocksHigher(
            const std::span<char> inName , 
            const std::span<char> outName, 
            std::size_t newLevel) {
        ProjectIO::setFileForProgram(inName, ProjectIO::FileModeCode::inputBinary);
        ProjectIO::setFileForProgram(outName, ProjectIO::FileModeCode::outputBinary);
        prepLevelChange(true, newLevel);
    }

    /**
     * @brief Tailored function to set program up for this endpoint.
     *
     * @param inName    String that holds the in file name [stdin default].
     * @param outName   String that holds the out file name [stdout default].
     *
     * @assumption      Files exist.
     */
    void initForBlocksToBlocksLower(
            const std::span<char> inName , 
            const std::span<char> outName, 
            std::size_t newLevel) {
        ProjectIO::setFileForProgram(inName, ProjectIO::FileModeCode::inputBinary);
        ProjectIO::setFileForProgram(outName, ProjectIO::FileModeCode::outputBinary);
        prepLevelChange(false, newLevel);
    }

    /**
     * @brief Tailored function to set program up for this endpoint.
     *
     * @param inName    String that holds the in file name [stdin default].
     * @param outName   String that holds the out file name [stdout default].
     *
     * @assumption      Files exist.
     */
    void initForBlocksToPrimes(const std::span<char> inName , const std::span<char> outName) {
        ProjectIO::setFileForProgram(inName, ProjectIO::FileModeCode::inputBinary);
        ProjectIO::setFileForProgram(outName, ProjectIO::FileModeCode::outputText);
    }
}

// TODO Find a place for storing in out buffers or at least the sizes needed
// TODO Data needs to be ordered before coming into this namespace
// TODO add option 5 to go from higher to lower and lower to higher
namespace InitData {

    /**
     * @brief Will set the program files up based on options given
     *
     * @param inName    String that holds the in file name [stdin default].
     * @param outName   String that holds the out file name [stdout default].
     * @param level     Number indicating the desired compression.
     * @param option    Number holding the io option. (need to create an enum).
     */
    void initProgramData(
            const std::span<char> inName, 
            const std::span<char> outName, 
            std::size_t level, 
            std::size_t option) {
        switch (option) {
            case 0u: initForPrimesToBlocks(inName, outName); break;
            case 1u: initForBlocksToBlocksHigher(inName, outName, level); break;
            case 2u: initForBlocksToBlocksLower(inName, outName, level); break;
            case 3u: initForBlocksToPrimes(inName, outName); break;
            default: perror("option not found");
        }
    }
}
