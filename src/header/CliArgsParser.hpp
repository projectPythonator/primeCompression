#ifndef CLI_ARGS_PARSER_HPP
#define CLI_ARGS_PARSER_HPP

#include "FileSystemIncludes.hpp"
#include "ContainerIncludes.hpp"
#include "IntegralIncludes.hpp"
#include "TestingIncludes.hpp"
#include "UtilityIncludes.hpp"

namespace Parser {
    class ProjectSettings {
        private:
            std::vector<bool> staticSet;
            std::vector<bool> projectSet;
            std::string projectFileName;
            std::size_t projectThreadCount;
            std::size_t projectCompressionLevel;
        public:
            ProjectSettings();

            /**
             * @brief   Call to handle strings that don't fall under the option choices.
             *
             * @param token         string that holds the current cli arguement.
             * @param fileName      string we use to store if it is a file name
             * @param threadCount   number we use to store token if it is a number.
             */
            void handleNotOption(const std::span<const char>);


            bool scanStatic(int, char* []);

            void scanProject(int, char *[]);

            /**
             * @brief   Call to parse data from the cli args.
             *
             * @param argc      Standard c main cli args, the number.
             * @param argv      Standard c main cli args, the strings.
             * @param fileName  Will hold any file names we get.
             * @param values    Will hold any number based arguements we get.
             */
            bool handleArgs(int, char*[]);

            void afterFix();

            bool isVerbose();
            bool isStdout(); 
            bool isTest();
            bool isBinFile();
            bool isForce();
            bool isDecompress();
            bool isRecompress();
    };

}

#endif
