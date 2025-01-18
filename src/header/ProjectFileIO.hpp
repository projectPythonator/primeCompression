#ifndef PROJECT_FILE_IO_HPP
#define PROJECT_FILE_IO_HPP

#include "IntegralTypeIncludes.hpp"
#include "ContainerIncludes.hpp"
#include "UtilityIncludes.hpp"
#include <cinttypes> // for fixed width scan and print types

// TODO fix typing am going to migrate to using fstream idk how good or bad it will be
namespace ProjectIO {
    inline bool eof_not_read = true;
    enum FileModeCode {
        inputText,
        inputBinary,
        outputText,
        outputBinary
    };
    
    void setOurBufSize(FILE *);
    void checkOpenFile(FILE *);

    void writeBlock_1Byte(const std::span<const std::uint8_t>);
    void writeBlock_8Byte(const std::span<const std::uint64_t>);

    void writeBlockOfText(const std::span<std::uint8_t>);
    void flushBuffer(const std::span<const std::uint8_t>);

    std::size_t readTillNL(const std::span<std::uint8_t>);
    std::size_t readBlock_1Byte(const std::span<std::uint8_t>);

    std::size_t readBlockNBytes(const std::span<std::uint8_t>);
    std::size_t readBlock_8Byte(const std::span<std::uint64_t>); 

    FILE * openStreamInGivenMode(const std::span<const char>, const std::span<const char>, FILE *);

    void setFileForProgram(std::span<char>, FileModeCode);

    std::size_t readBlockTillNL(const std::span<std::uint8_t>);
    std::size_t setIndexLocations(const std::span<const std::uint8_t>, const std::span<std::size_t>);
    std::size_t getNextTextBlock(const std::span<std::uint8_t>, const std::span<std::size_t>);
}

#endif
