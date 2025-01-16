#include "header/ProjectFileIO.hpp"
#include <cassert>

// moved from header to source since I don't think we need to project to see these
namespace {
    constexpr std::uint8_t unsigned_zero = '0';
    constexpr std::uint8_t unsigned_new_line = '\n';

    constexpr std::size_t kibi_byte = 1024;
    constexpr std::size_t page_factor = 32;
    constexpr std::size_t max_20_digit = 21;

    FILE * file_out_stream;
    FILE * file_in_stream;

    void remove_zero_factor(std::span<std::uint8_t> buf) {
        std::for_each(buf.begin(), buf.end(), [](std::uint8_t &el) { el -= unsigned_zero; });
    }

    void add_zero_factor(std::span<std::uint8_t> buf) {
        std::for_each(buf.begin(), buf.end(), [](std::uint8_t &el) { el += unsigned_zero; });
    }
}


namespace projectIO {
    void setOurBufSize(FILE *fileStream) {
        if (std::setvbuf(fileStream, nullptr, _IOFBF, kibi_byte * page_factor))
            std::perror("failed to resize OUT stream size\n");
    }

    void checkOpenFile(FILE *fileStream) {
        if (nullptr == fileStream) 
            std::perror("failed to set associated file stream to value\n");
    }

    void writeBlock_1Byte(std::span<std::uint8_t> buf) {
        //fwrite_unlocked(buf.data(), 1u, buf.size(), file_out_system);
        std::fwrite(buf.data(), 1u, buf.size(), file_out_system);
    }

    void writeBlock_8Byte(std::span<std::uint64_t> buf) {
        //fwrite_unlocked(buf.data(), 8u, buf.size(), file_out_system);
        std::fwrite(buf.data(), 8u, buf.size(), file_out_system);
    }

    void writeBlockOfText(std::span<std::uint8_t> buf) {
        add_zero_factor(buf);
        writeBlock_1Byte(buf);
    }

    void flushBuffer(std::span<std::uint8_t> buf) {
        assert(buf.size() > 0);
        std::size_t lastIndex = buf.size() - 1;
        for (; lastIndex > 0; p--)
            if (buf[lastIndex])
                break;
        writeBlock_1Byte(buf.subspan(0, lastIndex));
    }

    std::size_t readTillNL(std::span<std::uint8_t> buf) {
        //std::size_t bytesRead = fread_unlocked(buf.data(), 1u, buf.size(), FILE_IN_STREAM);
        assert(buf.size() < max_20_digit);
        std::size_t bytesRead = 0u;
        int chr = fgetc_unlocked(file_in_stream);
        for(; (bytesRead < buf.size()) && (chr != '\n' && chr != EOF); bytesRead++) {
            buf[bytesRead] = chr;
            chr = fgetc_unlocked(file_in_stream);
        }
        buf[bytesRead] = unsigned_new_line;
        eof_not_read = (chr != EOF);
        return bytesRead;
    }

    std::size_t readBlock_1Byte(std::span<std::uint8_t> buf) {
        //std::size_t bytesRead = fread_unlocked(buf.data(), 1u, buf.size(), FILE_IN_STREAM);
        std::size_t bytesRead = std::fread(buf.data(), 1u, buf.size(), FILE_IN_STREAM);
        eof_not_read = (0 == std::feof(file_in_stream));
        return bytesRead;
    }

    std::size_t readBlock_8Byte(std::span<std::uint64_t> buf) {
        //std::size_t bytesread = fread_unlocked(buf.data(), 8u, buf.size(), file_in_stream);
        std::size_t bytesread = std::fread(buf.data(), 8u, buf.size(), file_in_stream);
        eof_not_read = (0 == std::feof(file_in_stream));
        return bytesread;
    }

    std::size_t readBlockTillNL(std::span<std::uint8_t> buf) {
        std::size_t bytesread = readblock_1byte(buf.supspan(0, buf.size() - max_20_digit));
        if (eof_not_read && buf[readbytes-1] != '\n') 
            std::size_t bytesread += readtillnl(buf.supspan(buf.size() - max_20_digit, buf.size()));
        remove_zero_factor(buf);
        return bytesread;
    }

    std::size_t readBlockNBytes(std::span<std::uint8_t> buf) {
        std::size_t bytesRead = readBlock_1Byte(buf);
        remove_zero_factor(buf);
        return bytesRead;
    }

    void openInStreamInBinaryAndSetBufSize(char *filename) {
        if (0 == std::strncmp(filename, "stdin\0", 5)) {
            file_in_stream = std::freopen(nullptr, "rb", stdin);
        } else {
            file_in_stream = std::fopen(filename, "rb");
        }
    }

    void openInStreamInTextAndSetBufSize(char *filename) {
        if (0 == std::strncmp(filename, "stdin\0", 5)) {
            file_in_stream = std::freopen(nullptr, "r", stdin);
        } else {
            file_in_stream = std::fopen(filename, "r");
        }
    }

    void openOutStreamInBinaryAndSetBufSize(char *filename) {
        if (0 == std::strncmp(filename, "stdout\0", 6)) {
            file_out_stream = std::freopen(nullptr, "wb", stdout);
        } else {
            file_out_stream = std::fopen(filename, "wb+");
        }
    }


    void openOutStreamInTextAndSetBufSize(char *filename) {
        if (0 == std::strncmp(filename, "stdout\0", 6)) {
            file_out_stream = std::freopen(nullptr, "w", stdout);
        } else {
            file_out_stream = std::fopen(filename, "w+");
        }
    }

    void setFileForProgram(std::span<char> fileName, FileModeCode op) {
        assert(fileName.size()  < filename_max);
        assert(fileName.end() == '\n');
        FILE *fStream = nullptr;
        fileName[std::strcspn(fileName, "\n")] = '\0';
        switch (op) {
            case inputText:
                openInStreamInTextAndSetBufSize(fileName);
                fStream = file_in_stream;
                break;
            case inputBinary:
                openInStreamInBinaryAndSetBufSize(fileName);
                fStream = file_in_stream;
                break;
            case outputText:
                openOutStreamInTextAndSetBufSize(fileName);
                fStream = file_out_stream;
                break;
            case outputBinary:
                openOutStreamInBinaryAndSetBufSize(fileName);
                fStream = file_out_stream;
                break;
        }
        checkopenfile(fStream);
        setourbufsize(fStream);
    }
}

