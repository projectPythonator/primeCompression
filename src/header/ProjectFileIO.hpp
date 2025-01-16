#ifndef SIEVE_FILE_IO_HPP
#define SIEVE_FILE_IO_HPP

#include "IntegralTypeIncludes.hpp"
#include "ContainersIncludes.hpp"
#include <cinttypes> // for fixed width scan and print types

// TODO better namespace name
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

    std::size_t readblocktillnl(std::span<std::uint8_t>);
    std::size_t readblocknbytes(std::span<std::uint8_t>);

    std::size_t readblock_8byte(std::span<std::uint64_t>); 

    void openinstreaminbinaryandsetbufsize(char *); 
    void openoutstreaminbinaryandsetbufsize(char *); 
    void openinstreamintextandsetbufsize(char *);
    void openoutstreamintextandsetbufsize(char *);

    void readinfoforprogram(std::span<char>, std::span<char>);
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
