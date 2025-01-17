#include "header/CliArgsParser.hpp"

// I think I am going with
// Prog [options] inputFile
// if inputfile isn't selected the stdin option must be used
namespace {
    constexpr std::size_t level_count = 12;
    constexpr std::size_t help_count = 2;
    constexpr std::size_t force_count = 2;

    constexpr std::string level_options[level_count] = {
        "-0",
        "-1",
        "-2",
        "-3",
        "-4",
        "-5",
        "-6",
        "-7",
        "-8",
        "-9",
        "--best",
        "--fast"
    };
    constexpr std::string help_options[help_count] = {
        "-h",
        "--help"
    };
    constexpr std::string force_options[force_count] = {
        "-f",
        "--force"
    };

}

namespace Parser {


}
