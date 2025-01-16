#ifndef PROJECT_FILE_IO_HPP
#define PROJECT_FILE_IO_HPP

#include "IntegralTypeIncludes.hpp"
#include "ContainersIncludes.hpp"
#include <cinttypes> // for fixed width scan and print types

// TODO fix typing am going to migrate to using fstream idk how good or bad it will be
namespace projectIO {
    inline bool eof_not_read = true;
    
    void setOurBufSize(FILE *);
    void checkOpenFile(FILE *);

    void writeBlock_1Byte(std::span<std::uint8_t>);
    void writeBlock_8Byte(std::span<std::uint64_t>);
    void flushBuffer(std::span<std::uint8_t>);

    std::size_t readTillNL(std::span<std::uint8_t>);
    std::size_t readBlock_1Byte(std::span<std::uint8_t>);

    std::size_t readBlockTillNL(std::span<std::uint8_t>);
    std::size_t readBlocknBytes(std::span<std::uint8_t>);

    std::size_t readBlock_8Byte(std::span<std::uint64_t>); 

    void openInStreamInBinaryAndSetBufsize(char *); 
    void openOutStreamInBinaryAndSetBufsize(char *); 
    void openInStreamInTextAndSetBufsize(char *);
    void openOutStreamInTextAndSetBufsize(char *);

    void readInfoForProgram(std::span<char>, std::span<char>);
}
// keeping this in case it happens to be faster
/*
void setOurBufSize(FILE *);
void checkOpenFile(FILE *);

void writeBuffer(uint8_t *, size_t); 
void writeBuffer_uint64_t(uint64_t *, size_t); 

void readBuffer(uint8_t *, size_t); 
void readBuffer_uint64_t(uint64_t *, size_t); 
void readBlockFromInfoFile(const char *, uint8_t *, size_t);

void openInStreamInBinaryAndSetBufSize(char *);
void openOutStreamInBinaryAndSetBufSize(char *);

void openInStreamInTextAndSetBufSize(char *);
void openOutStreamInTextAndSetBufSize(char *);

void readInfoForProgram(const char *, uint64_t &, uint64_t &);

void flushBuffer(uint8_t *, size_t);
void readBufferTillNL(char *, size_t); 
*/

#endif
