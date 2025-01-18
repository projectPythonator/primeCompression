#ifndef CLI_ARGS_PARSER_HPP
#define CLI_ARGS_PARSER_HPP

#include "FileSystemIncludes.hpp"
#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"
#include "UtilityIncludes.hpp"

namespace Parser {
    void handleNotOption(const std::span<const char>, std::span<char>, std::size_t &);

    void handleArg(const std::span<const char>, std::span<char>, std::span<std::size_t>);
    void handleArgs(int, char *, std::span<char>, std::span<std::size_t>);
}

#endif
