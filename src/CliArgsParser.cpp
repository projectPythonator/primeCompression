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

    constexpr std::array<std::string_view, 32> cli_options_values = {
        "-0",
        "--fast",
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
        
        "-h",
        "--help",

        "-f",
        "--force",

        "-j",
        "--jobs",

        "-t",
        "--test",

        "-c",
        "--stdout",
        "--to-stdout",

        "-L",
        "--license",

        "-V",
        "--version",

        "-d",
        "--decompress",
        "--uncompress",

        "-v",
        "--verbose"
    };

    constexpr std::array<cli_op_codes, 32> cli_options_codes = {
        level_0,
        level_1,
        level_1,
        level_2,
        level_3,
        level_4,
        level_5,
        level_6,
        level_6,
        level_6,
        level_6,
        level_6,
        
        help_op,
        help_op,

        force_op,
        force_op,

        job_op,
        job_op,

        test_op,
        test_op,

        stdout_op,
        stdout_op,
        stdout_op,

        license_op,
        license_op,

        version_op,
        version_op,

        decompress_op,
        decompress_op,
        decompress_op,

        verbose_op,
        verbose_op
    };
    bool isNumber(const std::span<const char> token) {
        return std::all_of(token.begin(), token.end(), [](auto &el) { return std::isdigit(el); } );
    }
 
    bool isValidFile(const std::span<const char> token) {
        std::filesystem::path filePath(token.begin(), token.end());
        return std::filesystem::exists(filePath);
    }

   cli_op_codes last_op;
}

namespace Parser {

    void handleNotOption(const std::span<const char> token, std::span<char> fileName, std::size_t &threadCount) {
        if (isNumber(token)) {
            if (last_op != job_op) {
                perror("Last option was not -T");
                return;
            }
            threadCount = stoull(std::string(token.begin(), token.end()));
        } else if (isValidFile(token)) {
            std::copy(token.begin(), token.end(), fileName.begin());
        } else {
            perror("File name given was not valid");
        }
    }

    std::size_t isOption(std::span<const char> token) {
        std::basic_string_view token_view(token.data(), token.size());
        std::size_t index = 0;
        for (const auto &option: cli_options_values) {
            if (token_view == option) 
                break;
            index++;
        }
        return index;
    }

    void handle_arg(cli_op_codes op) {
        switch (op) {
            case level_0: break;
            case level_1: break;
            case level_2: break;
            case level_3: break;
            case level_4: break;
            case level_5: break;
            case level_6: break;
            case job_op: break;
            case help_op: break;
            case test_op: break;
            case force_op: break;
            case stdout_op: break;
            case license_op: break;
            case version_op: break;
            case verbose_op: break;
            case decompress_op: break;
        }
    }

    void handleArg(const std::span<const char> token, std::span<char> fileName, std::span<std::size_t> values) {
        std::size_t isOption(token)

    }

    void handleArgs() {

    }
}
