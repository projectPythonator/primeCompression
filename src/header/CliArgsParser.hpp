#ifndef CLI_ARGS_PARSER_HPP
#define CLI_ARGS_PARSER_HPP

#include "FileSystemIncludes.hpp"
#include "ContainerIncludes.hpp"
#include "IntegralIncludes.hpp"
#include "UtilityIncludes.hpp"

namespace Parser {
    /**
     * @brief   Call to handle strings that don't fall under the option choices.
     *
     * @param token         string that holds the current cli arguement.
     * @param fileName      string we use to store if it is a file name
     * @param threadCount   number we use to store token if it is a number.
     */
    void handleNotOption(const std::span<const char>, std::span<char>, std::size_t &);

    /**
     * @brief   Call to parse data from the cli args.
     *
     * @param argc      Standard c main cli args, the number.
     * @param argv      Standard c main cli args, the strings.
     * @param fileName  Will hold any file names we get.
     * @param values    Will hold any number based arguements we get.
     */
    void handleArgs(int, char *, std::span<char>, std::span<std::size_t>);
}

#endif
