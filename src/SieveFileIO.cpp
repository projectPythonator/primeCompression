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
