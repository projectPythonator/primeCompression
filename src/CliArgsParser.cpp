#include "header/CliArgsParser.hpp"

// I think I am going with
// Prog [options] inputFile
// if inputfile isn't selected the stdin option must be used
namespace {
    enum cli_op_codes {
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
    };

    std::unordered_map<std::string, cli_op_codes> cli_options;
        /*
        {"--fast", level_1},
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
    };*/
    void init_cli_options() {
        cli_options.emplace("--fast", level_1);
        cli_options.emplace("-0", level_0);
        cli_options.emplace("-1", level_1);
        cli_options.emplace("-2", level_2);
        cli_options.emplace("-3", level_3);
        cli_options.emplace("-4", level_4);
        cli_options.emplace("-5", level_5);
        cli_options.emplace("-6", level_6);
        cli_options.emplace("-7", level_6);
        cli_options.emplace("-8", level_6);
        cli_options.emplace("-9", level_6);
        cli_options.emplace("--best", level_6);
        
        cli_options.emplace("-h"    , help_op);
        cli_options.emplace("--help", help_op);

        cli_options.emplace("-f"       , force_op);
        cli_options.emplace("--force"  , force_op);

        cli_options.emplace("-j"       , job_op);
        cli_options.emplace("--jobs"   , job_op);

        cli_options.emplace("-t"       , test_op);
        cli_options.emplace("--test"   , test_op);

        cli_options.emplace("-c"           , stdout_op);
        cli_options.emplace("--stdout"     , stdout_op);
        cli_options.emplace("--to-stdout"  , stdout_op);

        cli_options.emplace("-L"           , license_op);
        cli_options.emplace("--license"    , license_op);

        cli_options.emplace("-V"           , version_op);
        cli_options.emplace("--version"    , version_op);

        cli_options.emplace("-d"           , decompress_op);
        cli_options.emplace("--decompress" , decompress_op);
        cli_options.emplace("--uncompress" , decompress_op);

        cli_options.emplace("-v"           , verbose_op);
        cli_options.emplace("--verbose"    , verbose_op);
    }

}

namespace Parser {


    void preset() {
        init_cli_options();
    }

}
