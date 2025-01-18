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

    enum class cli_project_switches {
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
        decompress_op,
        default_op
    };

    constexpr std::array<std::string_view, 30> cli_project_options = {
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

    constexpr std::array<cli_project_switches, 30> cli_project_codes = {
        cli_project_switches::level_0,
        cli_project_switches::level_1,
        cli_project_switches::level_1,
        cli_project_switches::level_2,
        cli_project_switches::level_3,
        cli_project_switches::level_4,
        cli_project_switches::level_5,
        cli_project_switches::level_6,
        cli_project_switches::level_6,
        cli_project_switches::level_6,
        cli_project_switches::level_6,
        cli_project_switches::level_6,
        cli_project_switches::bin_op,
        cli_project_switches::bin_op,
        cli_project_switches::job_op,
        cli_project_switches::job_op,
        cli_project_switches::test_op,
        cli_project_switches::test_op,
        cli_project_switches::force_op,
        cli_project_switches::force_op,
        cli_project_switches::stdout_op,
        cli_project_switches::stdout_op,
        cli_project_switches::stdout_op,
        cli_project_switches::verbose_op,
        cli_project_switches::verbose_op,
        cli_project_switches::recompress_op,
        cli_project_switches::recompress_op,
        cli_project_switches::decompress_op,
        cli_project_switches::decompress_op,
        cli_project_switches::decompress_op
    };

    // these codes print info then force exit the prog
    // first one seen is used
    enum class cli_static_switches {
        help_op,
        license_op,
        version_op,
        default_op
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
        cli_static_switches::help_op,
        cli_static_switches::help_op,
        cli_static_switches::license_op,
        cli_static_switches::license_op,
        cli_static_switches::version_op,
        cli_static_switches::version_op
    };

    cli_static_switches last_static = cli_static_switches::default_op;
    cli_project_switches last_project = cli_project_switches::default_op;

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

    void handleStaticSwitches(cli_static_switches op) {
        switch (op) {
            case cli_static_switches::help_op: break;
            case cli_static_switches::license_op: break;
            case cli_static_switches::version_op: break;
            case cli_static_switches::default_op: break;
        }
    }

    void handleProjectSwitches(cli_project_switches op) {
        switch (op) {
            case cli_project_switches::level_0: break;
            case cli_project_switches::level_1: break;
            case cli_project_switches::level_2: break;
            case cli_project_switches::level_3: break;
            case cli_project_switches::level_4: break;
            case cli_project_switches::level_5: break;
            case cli_project_switches::level_6: break;
            case cli_project_switches::bin_op: break;
            case cli_project_switches::job_op: break;
            case cli_project_switches::test_op: break;
            case cli_project_switches::force_op: break;
            case cli_project_switches::stdout_op: break;
            case cli_project_switches::verbose_op: break;
            case cli_project_switches::recompress_op: break;
            case cli_project_switches::decompress_op: break;
            case cli_project_switches::default_op: break;
        }
    }


}

namespace Parser {
    void handleNotOption(const std::span<const char> token, std::span<char> fileName, std::size_t &threadCount) {
        if (isNumber(token)) {
            if (last_project != cli_project_switches::job_op) {
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
    void handleArg(const std::span<const char> token, std::span<char> fileName, std::span<std::size_t> values) {


    }
    */

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

        i = 0;
        for (std::string_view arg: std::span(argv, argc)) {
            if (i == 0)
                continue;
            if (isProjectSwitch(arg)) {
                handleProjectSwitches(cli_project_codes[projectIndex(arg)]);
                return;
            } else {
                fileName[0] = 'a';
                values[0] = 0u;

            }
            i++;
        }

    }
}
