#include "header/CliArgsParser.hpp"

// I think I am going with
// Prog [options] inputFile
// if inputfile isn't selected the stdin option must be used
// fix naming for handleSwitches names
// look into getting a more dynamic args parser
namespace {

    constexpr std::size_t max_compress_level = 6u;
    
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

    //cli_static_switches last_static = cli_static_switches::default_op;
    cli_project_switches last_project = cli_project_switches::default_op;

    std::size_t staticIndex(const std::span<const char> token) {
        std::basic_string_view token_view(token.data(), token.size());
        std::size_t i = 0;
        for (const auto &option: cli_static_options) {
            if (token_view == option) 
                return i;
            i++;
        }
        return i;
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

    bool isStaticSwitch(const std::span<const char> token) {
        return (staticIndex(token) < cli_static_options.size());
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

    std::size_t handleStaticSwitches(cli_static_switches op) {
        switch (op) {
            case cli_static_switches::help_op:      return 0u;
            case cli_static_switches::license_op:   return 1u;
            case cli_static_switches::version_op:   return 2u;
            case cli_static_switches::default_op:   return 3u;
        }
        return 3u;
    }

    std::size_t handleProjectSwitches(cli_project_switches op) {
        switch (op) {
            case cli_project_switches::level_0: return 0u;
            case cli_project_switches::level_1: return 1u;
            case cli_project_switches::level_2: return 2u;
            case cli_project_switches::level_3: return 3u;
            case cli_project_switches::level_4: return 4u;
            case cli_project_switches::level_5: return 5u;
            case cli_project_switches::level_6: return 6u;
            case cli_project_switches::bin_op:  return 7u;
            case cli_project_switches::job_op:  return 8u;
            case cli_project_switches::test_op: return 9u;
            case cli_project_switches::force_op:        return 10u;
            case cli_project_switches::stdout_op:       return 11u;
            case cli_project_switches::verbose_op:      return 12u;
            case cli_project_switches::recompress_op:   return 13u;
            case cli_project_switches::decompress_op:   return 14u;
            case cli_project_switches::default_op:      return 15u;
        }
        return 15u;
    }
}

// TODO missing the function that holds handles non static options.
// TODO add getters 
// TODO add fix up function
namespace Parser {
    ProjectSettings::ProjectSettings() {
        std::size_t len = handleProjectSwitches(cli_project_switches::default_op) + 1u;
        staticSet.assign(cli_static_options.size(), false);

        projectSet.assign(len, false);
        projectFileName = "stdin";
        projectThreadCount = 1;
        projectCompressionLevel = 1;
    }

    /**
     * @brief Tailored function to handle numbers and file names.
     *
     * @param token         string that holds the current cli arguement.
     * @param fileName      string we use to store if it is a file name
     * @param threadCount   number we use to store token if it is a number.
     */
    void ProjectSettings::handleNotOption(const std::span<const char> token) {
        if (isNumber(token)) {
            if (last_project != cli_project_switches::job_op) {
                perror("Last option was not -T");
                return;
            }
            projectThreadCount = stoull(std::string(token.begin(), token.end()));
        } else if (isValidFile(token)) {
            std::copy(token.begin(), token.end(), projectFileName.begin());
            // change to string view
        } else {
            perror("File name given was not valid");
            // abort
        }
    }


    bool ProjectSettings::scanStatic(int argc, char *argv[]) {
        // use external ind i if no compile
        for (std::string_view arg: std::span(argv+1, argc)) {
            if (isStaticSwitch(arg)) {
                std::size_t index = staticIndex(arg);
                index = handleStaticSwitches(cli_static_codes[index]);
                staticSet[index] = true;
                return true;
            }
        }
        return false;
    }

    void ProjectSettings::scanProject(int argc, char *argv[]) {
        for (std::string_view arg: std::span(argv+1, argc)) {
            if (isProjectSwitch(arg)) {
                std::size_t optionIndex = handleProjectSwitches(cli_project_codes[projectIndex(arg)]);
                projectSet[optionIndex] = true;
                return;
            } else {
                ProjectSettings::handleNotOption(arg);
            }
        }
    }

    /**
     * @brief   Walks the cli args and then sets options accordingly
     *
     * @param argc      Standard c main cli args, the number.
     * @param argv      Standard c main cli args, the strings.
     * @param fileName  Will hold any file names we get.
     * @param values    Will hold any number based arguements we get.
     *
     * TODO still need to add ability to exit after finding this option.
     * TODO fix file name to handle more than one
     */
    bool ProjectSettings::handleArgs(int argc, char *argv[]) {
        if (ProjectSettings::scanStatic(argc, argv))
            return false;
        ProjectSettings::scanProject(argc, argv);
        return true;
    }

    // need error checking on having a level but requesting decopression
    void ProjectSettings::afterFix() {
        if (projectSet[handleProjectSwitches(cli_project_switches::stdout_op)])
            projectFileName = "stdin";
        for (std::size_t i = 0; i < max_compress_level; i++)
            if (projectSet[i])
                projectCompressionLevel = i;
        assert((isRecompress() ^ isDecompress()) || !(isRecompress() && isDecompress()));
        // assert for test and compression level
        // force does nothing rightnow
        // fix output file name
        // need to program verbose to actually do something
    }

    bool ProjectSettings::isVerbose() { 
        return projectSet[handleProjectSwitches(cli_project_switches::verbose_op)];
    }

    bool ProjectSettings::isStdout() { 
        return projectSet[handleProjectSwitches(cli_project_switches::stdout_op)];
    }

    bool ProjectSettings::isTest() { 
        return projectSet[handleProjectSwitches(cli_project_switches::test_op)];
    }

    bool ProjectSettings::isBinFile() { 
        return projectSet[handleProjectSwitches(cli_project_switches::bin_op)];
    }

    bool ProjectSettings::isForce() { 
        return projectSet[handleProjectSwitches(cli_project_switches::force_op)];
    }

    bool ProjectSettings::isDecompress() { 
        return projectSet[handleProjectSwitches(cli_project_switches::decompress_op)];
    }

    bool ProjectSettings::isRecompress() { 
        return projectSet[handleProjectSwitches(cli_project_switches::recompress_op)];
    }
}
