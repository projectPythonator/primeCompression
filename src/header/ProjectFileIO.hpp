#ifndef PROJECT_FILE_IO_HPP
#define PROJECT_FILE_IO_HPP

#include "IntegralIncludes.hpp"
#include "ContainerIncludes.hpp"
#include "TestingIncludes.hpp"
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

    /**
     * @brief Call when you need to print block of text
     *
     * @param buf   span of bytes to print
     * @assumption  buffer isn't normalized with the '0' char
     */
    void writeBlockOfText(const std::span<std::uint8_t>);

    /**
     * @brief Call when you need to print block of binary 8 byte numbers
     *
     * @param buf   span of numbers to print
     */
    void writeBlockOfBinary(const std::span<std::uint64_t>);

    // removed void flushBuffer(const std::span<const std::uint8_t>);

    /**
     * @brief Call when you want to read a block of bytes.
     *
     * @param buf   span that will hold the bytes read in.
     * @return      count of bytes read.
     */
    std::size_t readBlock_1Byte(const std::span<std::uint8_t>);

    /**
     * @brief Call when you want to read a block of numbers in 8 byte format.
     *
     * @param buf   span that will hold the numbers in it.
     * @return      count of numbers read.
     */
    std::size_t readBlock_8Byte(const std::span<std::uint64_t>);

    /**
     * @brief Call when you want to read a set number of bytes from stream.
     *
     * @param buf   span that will hold the bytes.
     * @return      count of bytes read.
     */
    std::size_t readBlockNBytes(const std::span<std::uint8_t>);

    /**
     * @brief Call only when you want to read one number from stream.
     *
     * @param buf   span that will hold the number.
     * @return      count of bytes read.
     *
     * @assumption  buffer size <= 20 (checked).
     */
    std::size_t readTillNL(const std::span<std::uint8_t>);

    /**
     * @brief Call only when you want to read numbers up till a newline
     *
     * @param buf   span that will hold the numbers in a buffer.
     * @return      count of bytes read.
     */
    std::size_t readBlockTillNL(const std::span<std::uint8_t>);

    /**
     * @brief Call when you want both a text block and mapping of newlines.
     *
     * @param buf       span that will hold the block of characters.
     * @param indices   span that holds positions of newlines.
     * @return          count of bytes read.
     */
    std::size_t getNextTextBlock(const std::span<std::uint8_t>, const std::span<std::size_t>);

    /**
     * @brief Call when you want to open a file for the program.
     *
     * @param fileName  span holding name of file. (stdin, stdout for those files)
     * @param op        enum for mapping of an operation code (found in header)
     */
    void setFileForProgram(std::span<char> fileName, FileModeCode op);
}

#endif
