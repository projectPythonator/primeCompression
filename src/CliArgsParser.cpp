#include "header/CliArgsParser.hpp"

// I think I am going with
// Prog [options] inputFile
// if inputfile isn't selected the stdin option must be used
namespace {
    /*
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
    */

    enum cli_project_switches {
        level_0,
        level_1,
        level_2,
        level_3,
        level_4,
        level_5,
        level_6,
        bin_op,
        job_op,
        test_op,
        force_op,
        stdout_op,
        verbose_op,
        recompress_op,
        decompress_op
    };

    constexpr std::array<std::string_view, 31> cli_project_options = {
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

        "-b",
        "--binary",
        
        "-j",
        "--jobs",

        "-t",
        "--test",

        "-f",
        "--force",

        "-c",
        "--stdout",
        "--to-stdout",

        "-v",
        "--verbose"

        "-R",
        "--recompress",

        "-d",
        "--decompress",
        "--uncompress",
    };

    constexpr std::array<cli_project_switches, 31> cli_project_codes = {
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
        bin_op,
        bin_op,
        job_op,
        job_op,
        test_op,
        test_op,
        force_op,
        force_op,
        stdout_op,
        stdout_op,
        stdout_op,
        verbose_op,
        verbose_op,
        recompress_op,
        recompress_op,
        decompress_op,
        decompress_op,
        decompress_op
    };

    // these codes print info then force exit the prog
    // first one seen is used
    enum cli_static_switches {
        help_op,
        license_op,
        version_op,
    };

    constexpr std::array<std::string_view, 6> cli_static_options = {
        "-h",
        "--help",
        "-L",
        "--license",
        "-V",
        "--version"
    };

    constexpr std::array<cli_static_switches, 6> cli_static_codes = {
        help_op,
        help_op,
        license_op,
        license_op,
        version_op,
        version_op
    };

    cli_static_switches last_static;
    cli_project_switches last_project;

    std::size_t staticIndex(const std::span<const char> token) {
        std::basic_string_view token_view(token.data(), token.size());
        std::size_t i = 0;
        for (const auto &option: cli_static_options) {
            if (token_view == option)  {
                last_static = cli_static_codes[i];
                return i;
            }
            i++;
        }
        return i;
    }

    bool isStaticSwitch(const std::span<const char> token) {
        return (staticIndex(token) < cli_static_options.size());
    }

    std::size_t projectIndex(const std::span<const char> token) {
        std::basic_string_view token_view(token.data(), token.size());
        std::size_t i = 0;
        for (const auto &option: cli_project_options) {
            if (token_view == option)  {
                last_project = cli_project_codes[i];
                return i;
            }
            i++;
        }
        return i;
    }

    bool isProjectSwitch(const std::span<const char> token) {
        return (projectIndex(token) < cli_project_options.size());
    }

    bool isNumber(const std::span<const char> token) {
        return std::all_of(token.begin(), token.end(), [](auto &el) { return std::isdigit(el); } );
    }
 
    bool isValidFile(const std::span<const char> token) {
        std::filesystem::path filePath(token.begin(), token.end());
        return std::filesystem::exists(filePath);
    }

}

namespace Parser {
    void handleNotOption(const std::span<const char> token, std::span<char> fileName, std::size_t &threadCount) {
        if (isNumber(token)) {
            if (last_project != job_op) {
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

    /*
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
    */
    void handleStaticSwitches(cli_static_switches op) {
        switch (op) {
            case help_op: break;
            case license_op: break;
            case version_op: break;
        }
    }

    void handleProgramSwitches() {
        cli_project_switches op = level_0;
        switch (op) {
            case level_0: break;
            case level_1: break;
            case level_2: break;
            case level_3: break;
            case level_4: break;
            case level_5: break;
            case level_6: break;
            case bin_op: break;
            case job_op: break;
            case test_op: break;
            case force_op: break;
            case stdout_op: break;
            case verbose_op: break;
            case recompress_op: break;
            case decompress_op: break;
        }
    }

    void handleArg(const std::span<const char> token, std::span<char> fileName, std::span<std::size_t> values) {

    }

    void handleArgs(int argc, char *argv[], std::span<char> fileName, std::span<std::size_t> values) {
        std::size_t i = 0;
        for (std::string_view arg: std::span(argv, argc)) {
            if (i == 0)
                continue;
            if (isStaticSwitch(arg)) {
                handleStaticSwitches(cli_static_codes[staticIndex(arg)]);
                return;
            }
            i++;
        }
    }
}
