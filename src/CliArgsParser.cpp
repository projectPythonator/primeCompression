#include "header/CliArgsParser.hpp"

// I think I am going with
// Prog [options] inputFile
// if inputfile isn't selected the stdin option must be used
namespace {
    constexpr std::size_t level_count = 12;
    constexpr std::size_t help_count = 2;
    constexpr std::size_t force_count = 2;
    enum op_codes {
        level_0,
        level_1,
        level_2,
        level_3,
        level_4,
        level_5,
        level_6,
        job_op,
        help_op,
        test_op,
        force_op,
        stdout_op,
        license_op,
        version_op,
        verbose_op,
        decompress_op
    }

    constexpr std::unordered_map<std::string, op_codes> cli_options = {
        {"-0", level_0},
        {"-1", level_1},
        {"-2", level_2},
        {"-3", level_3},
        {"-4", level_4},
        {"-5", level_5},
        {"-6", level_6},
        {"-7", level_6},
        {"-8", level_6},
        {"-9", level_6},
        {"--fast", level_1},
        {"--best", level_6},
        
        {"-h"    , help_op},
        {"--help", help_op},

        {"-f"       , force_op},
        {"--force"  , force_op},

        {"-j"       , job_op},
        {"--jobs"   , job_op},

        {"-t"       , test_op},
        {"--test"   , test_op},

        {"-c"           , stdout_op},
        {"--stdout"     , stdout_op},
        {"--to-stdout"  , stdout_op},

        {"-L"           , license_op},
        {"--license"    , license_op},

        {"-V"           , version_op},
        {"--version"    , version_op},

        {"-d"           , decompress_op},
        {"--decompress" , decompress_op},
        {"--uncompress" , decompress_op},


        {"-v"           , verbose_op},
        {"--verbose"    , verbose_op}
    };
}

namespace Parser {


}
