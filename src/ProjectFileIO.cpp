#include "header/ProjectFileIO.hpp"

// moved from header to source since I don't think we need to project to see these
namespace {
    constexpr std::uint8_t unsigned_zero = '0';
    constexpr std::uint8_t unsigned_new_line = '\n';
    constexpr std::uint8_t unsigned_line_break = unsigned_new_line - unsigned_zero;


    constexpr std::size_t kibi_byte = 1024;
    constexpr std::size_t page_factor = 32;
    constexpr std::size_t max_20_digit = 21;

    constexpr std::size_t text_block_max_numbers = kibi_byte * 4u;
    constexpr std::size_t text_block_size = kibi_byte * page_factor;

    // turn into enum if possible
    constexpr char wb_mode[3] = "wb";
    constexpr char rb_mode[3] = "rb";
    constexpr char wt_mode[3] = "w+";
    constexpr char rt_mode[2] = "r";

    FILE * file_out_stream = stdout;
    FILE * file_in_stream = stdin;

    
    void remove_zero_factor(const std::span<std::uint8_t> buf) {
        assert(buf.size() % 16 == 0);
        std::for_each(buf.begin(), buf.end(), [](std::uint8_t &el) { el -= unsigned_zero; });
    }

    void add_zero_factor(const std::span<std::uint8_t> buf) {
        std::for_each(buf.begin(), buf.end(), [](std::uint8_t &el) { el += unsigned_zero; });
    }
    
    void writeBlock_1Byte(const std::span<const std::uint8_t> buf) {
        std::fwrite(buf.data(), 1u, buf.size(), file_out_stream);
    }

    void writeBlock_8Byte(const std::span<const std::uint64_t> buf) {
        std::fwrite(buf.data(), 8u, buf.size(), file_out_stream);
    }

    std::size_t setIndexLocations(const std::span<const std::uint8_t> buf, const std::span<std::size_t> indices) {
        assert(indices.size() == text_block_max_numbers);
        assert(buf.size() <= text_block_size);
        std::size_t i = 0;
        for (std::size_t b = 0; b < buf.size(); b++)
            if (buf[b] == unsigned_line_break)
                indices[i++] = b;
        return i;
    }

    void setOurBufSize(FILE *fileStream) {
        if (std::setvbuf(fileStream, nullptr, _IOFBF, kibi_byte * page_factor))
            std::perror("failed to resize OUT stream size\n");
    }

    void checkOpenFile(FILE *fileStream) {
        if (nullptr == fileStream) 
            std::perror("failed to set associated file stream to value\n");
    }

    FILE *openStreamInGivenMode(
            const std::span<const char> fileName, 
            const std::span<const char> fileMode, 
            FILE *stream) {
        if (0 == std::strncmp(fileName.data(), "stdin\0", 5)) {
            stream = std::freopen(nullptr, fileMode.data(), stdin);
        } else if (0 == std::strncmp(fileName.data(), "stdout\0", 6)) {
            stream = std::freopen(nullptr, fileMode.data(), stdout);
        } else {
            stream = std::fopen(fileName.data(), fileMode.data());
        }
        return stream;
    }
}


// TODO add function to call 8byte write
namespace ProjectIO {

    /**
     * @brief print buffer of bytes
     * will adjust a buffer then print its bytes
     *
     * @param buf   span of bytes to print
     *
     * @assumption  buffer isn't normalized with the '0' char
     */
    void writeBlockOfText(const std::span<std::uint8_t> buf) {
        add_zero_factor(buf);
        writeBlock_1Byte(buf);
    }

    /**
     * @brief prints 8 byte nunmbers to binary file
     *
     * @param buf   span of numbers to print
     */
    void writeBlockOfBinary(const std::span<std::uint64_t> buf) {
        writeBlock_8Byte(buf);
    }

    // Removed flushBuffer

    /**
     * @brief reads a block of bytes then checks for EOF.
     *
     * @param buf   span that will hold the bytes read in.
     * @return      returns the number of bytes read.
     */
    std::size_t readBlock_1Byte(const std::span<std::uint8_t> buf) {
        std::size_t bytesRead = std::fread(buf.data(), 1u, buf.size(), file_in_stream);
        ProjectIO::eof_not_read = (0 == std::feof(file_in_stream));
        return bytesRead;
    }

    /**
     * @brief reads a block of 8 byte numbers, then checks for EOF.
     *
     * @param buf   span that will hold the numbers in it.
     * @return      returns the count of numbers read.
     */
    std::size_t readBlock_8Byte(const std::span<std::uint64_t> buf) {
        std::size_t bytesread = std::fread(buf.data(), 8u, buf.size(), file_in_stream);
        ProjectIO::eof_not_read = (0 == std::feof(file_in_stream));
        return bytesread;
    }

    /**
     * @brief calles read block then removes '0' from the buffer.
     *
     * @param buf   span that will hold the block of characters.
     * @return      returns the count of bytes read.
     */
    std::size_t readBlockNBytes(const std::span<std::uint8_t> buf) {
        std::size_t bytesRead = readBlock_1Byte(buf);
        remove_zero_factor(buf);
        return bytesRead;
    }

    /**
     * @brief reads a number till next newline.
     * is a helper function to read a number from the in stream.
     *
     * @param buf   span that will read in a number.
     * @return      count of bytes read.
     *
     * @assumption  buffer size <= 20 (checked).
     */
    std::size_t readTillNL(const std::span<std::uint8_t> buf) {
        assert(buf.size() < max_20_digit);
        std::size_t bytesRead = 0u;
        int chr = fgetc_unlocked(file_in_stream);
        for(; (bytesRead < buf.size()) && (chr != '\n' && chr != EOF); bytesRead++) {
            buf[bytesRead] = chr;
            chr = fgetc_unlocked(file_in_stream);
        }
        buf[bytesRead] = unsigned_new_line;
        ProjectIO::eof_not_read = (chr != EOF);
        return bytesRead;
    }

    /**
     * @brief reads a block of text that ends in a newline
     * Reads a chunk of a block, then reads a single number to ensure block ends in newline.
     *
     * @param buf   span that will hold the block of characters.
     * @return      count of bytes read.
     *
     * @assumption  buffer size <= 20 (checked).
     */
    std::size_t readBlockTillNL(const std::span<std::uint8_t> buf) {
        assert(buf.size() == text_block_size);
        std::size_t bytesRead = readBlock_1Byte(buf.subspan(0, buf.size() - max_20_digit));
        if (ProjectIO::eof_not_read && buf[bytesRead-1] != '\n') 
            bytesRead += readTillNL(buf.subspan(buf.size() - max_20_digit, buf.size()));
        remove_zero_factor(buf);
        return bytesRead;
    }

    /**
     * @brief reads block of text and map the positions of newlines.
     *
     * @param buf       span that will hold the block of characters.
     * @param indices   span that holds positions of newlines.
     * @return      count of bytes read.
     */
    std::size_t getNextTextBlock(const std::span<std::uint8_t> buf, const std::span<std::size_t> indices) {
        std::size_t bytesRead = readBlockTillNL(buf);
        return setIndexLocations(buf.subspan(0, bytesRead), indices);
    }

    /**
     * @brief opens file with given name based on code given.
     * Opens file, sets file stream, checks file, sets the buffer size.
     *
     * @param fileName  span holding name of file. (stdin, stdout for those files)
     * @param op        enum for mapping of an operation code (found in header)
     */
    void setFileForProgram(std::span<char> fileName, FileModeCode op) {
        assert(fileName.size()  < FILENAME_MAX);
        assert(fileName.size() > 0);
        assert(fileName[fileName.size() - 1] == '\n');
        FILE *fStream = nullptr;
        fileName[std::strcspn(fileName.data(), "\n")] = '\0';
        switch (op) {
            case inputText:
                fStream = openStreamInGivenMode(fileName, std::span<const char>(rt_mode), file_in_stream);
                break;
            case inputBinary:
                fStream = openStreamInGivenMode(fileName, std::span<const char>(rb_mode), file_in_stream);
                break;
            case outputText:
                fStream = openStreamInGivenMode(fileName, std::span<const char>(wt_mode), file_out_stream);
                break;
            case outputBinary:
                fStream = openStreamInGivenMode(fileName, std::span<const char>(wb_mode), file_out_stream);
                break;
        }
        checkOpenFile(fStream);
        setOurBufSize(fStream);
    }
}

