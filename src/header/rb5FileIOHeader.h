#pragma once 
#include "rb5GlobalIncludes.h"
#include <cstdio>
#include <cstring>

const size_t KIBIBYTE = 1024;
const size_t PAGE_FACTOR = 64;

inline FILE *FILE_OUT_STREAM;
inline FILE *FILE_IN_STREAM;

// does this instead need to be static??
inline bool EOF_NOT_READ = true;


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
