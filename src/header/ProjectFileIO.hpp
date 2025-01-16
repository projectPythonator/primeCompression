#ifndef PROJECT_FILE_IO_HPP
#define PROJECT_FILE_IO_HPP

#include "IntegralTypeIncludes.hpp"
#include "ContainersIncludes.hpp"
#include <cinttypes> // for fixed width scan and print types

// TODO fix typing am going to migrate to using fstream idk how good or bad it will be
namespace projectIO {
    inline bool eof_not_read = true;
    enum FileModeCode {
        inputText,
        inputBinary,
        outputText,
        outputBinary
    };
    
    void setOurBufSize(FILE *);
    void checkOpenFile(FILE *);

    void writeBlock_1Byte(std::span<std::uint8_t>);
    void writeBlock_8Byte(std::span<std::uint64_t>);

    void writeBlockOfText(std::span<std::uint8_t>);
    void flushBuffer(std::span<std::uint8_t>);

    std::size_t readTillNL(std::span<std::uint8_t>);
    std::size_t readBlock_1Byte(std::span<std::uint8_t>);

    std::size_t readBlockTillNL(std::span<std::uint8_t>);
    std::size_t readBlockNBytes(std::span<std::uint8_t>);

    std::size_t readBlock_8Byte(std::span<std::uint64_t>); 

    void openInStreamInBinaryAndSetBufSize(char *); 
    void openInStreamInTextAndSetBufSize(char *);
    void openOutStreamInBinaryAndSetBufSize(char *); 
    void openOutStreamInTextAndSetBufSize(char *);

    void setFileForProgram(std::span<char>, FileModeCode);
}

#endif
