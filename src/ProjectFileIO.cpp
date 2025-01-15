#include "header/SieveFileIO.hpp"

// TODO add in buffers potential
// moved from header to source since I don't think we need to project to see these
namespace {
    constexpr std::size_t kibiByte = 1024;
    constexpr std::size_t page_factor = 32;

    FILE * file_out_stream;
    FILE * file_in_stream;
}


namespace projectIO {
    void setOurBufSize(FILE *fileStream) {
        if (std::setvbuf(fileStream, nullptr, _IOFBF, KIBIBYTE * PAGE_FACTOR))
            std::perror("failed to resize OUT stream size\n");
    }

    void checkOpenFile(FILE *fileStream) {
        if (nullptr == fileStream) 
            std::perror("failed to set associated file stream to value\n");
    }

    void writeBuffer(uint8_t *buf, size_t bufSize) {
        //std::fwrite(buf, sizeof(uint8_t), bufSize, FILE_OUT_STREAM);
        fwrite_unlocked(buf, sizeof(uint8_t), bufSize, FILE_OUT_STREAM);
    }

    void writeBuffer_uint64_t(uint64_t *buf, size_t bufSize) {
        //std::fwrite(buf, sizeof(uint64_t), bufSize, FILE_OUT_STREAM);
        fwrite_unlocked(buf, sizeof(uint64_t), bufSize, FILE_OUT_STREAM);
    }


    void readBuffer(uint8_t *buf, size_t bufSize) {
        //std::fread(buf, sizeof(uint8_t), bufSize, FILE_IN_STREAM);
        fread_unlocked(buf, sizeof(uint8_t), bufSize, FILE_IN_STREAM);
        EOF_NOT_READ = (0 == std::feof(FILE_IN_STREAM));
    }

    void readBuffer_uint64_t(uint64_t *buf, size_t bufSize) {
        //std::fread(buf, sizeof(uint64_t), bufSize, FILE_IN_STREAM);
        fread_unlocked(buf, sizeof(uint64_t), bufSize, FILE_IN_STREAM);
        EOF_NOT_READ = (0 == std::feof(FILE_IN_STREAM));
    }

    void readBlockFromInfoFile(const char *fileName, uint8_t *block, size_t dataAmt) {
        char dataFileName[256] = "./data/";
        std::strcat(dataFileName, fileName);
        auto f = fopen(dataFileName, "rb");
        std::fread(block, 1, dataAmt, f);
        fclose(f);
    }

    void openInStreamInBinaryAndSetBufSize(char *fileName) {
        if (0 == std::strncmp(fileName, "STDIN\0", 5)) {
            FILE_IN_STREAM = std::freopen(nullptr, "rb", stdin);
        } else {
            FILE_IN_STREAM = std::fopen(fileName, "rb");
        }
    }

    void openOutStreamInBinaryAndSetBufSize(char *fileName) {
        if (0 == std::strncmp(fileName, "STDOUT\0", 6)) {
            FILE_OUT_STREAM = std::freopen(nullptr, "wb", stdout);
        } else {
            FILE_OUT_STREAM = std::fopen(fileName, "wb+");
        }
    }

    void openInStreamInTextAndSetBufSize(char *fileName) {
        if (0 == std::strncmp(fileName, "STDIN\0", 5)) {
            FILE_IN_STREAM = std::freopen(nullptr, "r", stdin);
        } else {
            FILE_IN_STREAM = std::fopen(fileName, "r");
        }
    }

    void openOutStreamInTextAndSetBufSize(char *fileName) {
        if (0 == std::strncmp(fileName, "STDOUT\0", 6)) {
            FILE_OUT_STREAM = std::freopen(nullptr, "w", stdout);
        } else {
            FILE_OUT_STREAM = std::fopen(fileName, "w+");
        }
    }

    void readInfoForProgram(const char *fileName, uint64_t &data1, uint64_t &data2) {
        char dataFileName[256] = "./data/";
        char outFileName[100];
        char inFileName[100];
        std::strcat(dataFileName, fileName);
        auto f = std::fopen(dataFileName, "r");
        if (nullptr == f)
            std::perror("failed to open arguements file for program\n");
        std::fscanf(f, "%" SCNu64 "\n", &data1);
        std::fscanf(f, "%" SCNu64 "\n", &data2);
        if (nullptr == std::fgets(outFileName, sizeof(outFileName), f)) {
            std::perror("failed to read the out stream file from args file\n");
            return;
        }
        if (nullptr == std::fgets(inFileName, sizeof(inFileName), f)) {
            std::perror("failed to read the in stream file from args file\n");
            return;
        }
        std::fclose(f);
        outFileName[std::strcspn(outFileName, "\n")] = '\0';
        inFileName[std::strcspn(inFileName, "\n")] = '\0';
        openOutStreamInBinaryAndSetBufSize(outFileName);
        checkOpenFile(FILE_OUT_STREAM);
        openInStreamInBinaryAndSetBufSize(inFileName);
        checkOpenFile(FILE_IN_STREAM);
        setOurBufSize(FILE_IN_STREAM);
        setOurBufSize(FILE_OUT_STREAM);
    }

    void flushBuffer(uint8_t *buf, size_t bufSize) {
        size_t lastIndex = 0;
        for (size_t p = 0; p < bufSize; p++)
            if (buf[p])
                lastIndex = p;
        writeBuffer(buf, lastIndex);
    }

    void readBufferTillNL(char *buf, size_t bufSize) {
        size_t readBytes = fread_unlocked(buf, 1, bufSize, FILE_IN_STREAM);
        EOF_NOT_READ = (0 == std::feof(FILE_IN_STREAM));
        if (EOF_NOT_READ && buf[readBytes-1] != '\n') {
            int chr = fgetc_unlocked(FILE_IN_STREAM);
            for (; chr != '\n' && chr != EOF; chr = fgetc_unlocked(FILE_IN_STREAM))
                buf[readBytes++] = chr;
            buf[readBytes] = '\n';
            EOF_NOT_READ = (chr != EOF);
        }
        //return readBytes;
    }
}

#include "rb5FileIOHeader.h"


