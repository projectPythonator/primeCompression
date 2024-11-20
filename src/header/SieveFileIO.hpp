#ifndef SIEVE_FILE_IO_HPP
#define SIEVE_FILE_IO_HPP

#include <cstdio>    // maybe change this to streams ?????
#include <cinttypes> // for fixed width scan and print types

// TODO include vectors and arrays
// TODO better namespace name
// TODO fix typing am going to migrate to using fstream idk how good or bad it will be
namespace projectIO {
    // does this instead need to be static??
    inline bool EOF_NOT_READ = true;

    // fix the typing on this
    void setOurBufSize(FILE *);
    void checkOpenFile(FILE *);

    void writeBlock(std::span<uint8_t>);
    void readBlock(std::span<uint8_t>);

    void readBlockFromInfoFile(const char *, std::span<uint8_t>);

    void openInStreamInBinaryAndSetBufSize(char *);
    void openOutStreamInBinaryAndSetBufSize(char *);

    void openInStreamInTextAndSetBufSize(char *);
    void openOutStreamInTextAndSetBufSize(char *);
   
    void readInfoForProgram(const char *, uint64_t &, uint64_t &);
    void readBufferTillNL(char *, size_t); 
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
