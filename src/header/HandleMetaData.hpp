#ifndef HANDLE_META_DATA_HPP
#define HANDLE_META_DATA_HPP
#include "ContainerIncludes.hpp"
#include "IntegralIncludes.hpp"
#include "ProjectFileIO.hpp"
#include "TestingIncludes.hpp"

namespace MetaDataInfo {

    class MetaData {
        private:
            std::string fileName = "";
            std::uint64_t startPrime{0};
            std::uint64_t compressionLevel{0};
        public:
            MetaData(const std::span<const char>, std::uint64_t, std::uint64_t);
            void writeMetaData();
            void readMetaData();

            std::uint64_t getCompressionLevel() { return compressionLevel; }
            std::uint64_t getStartPrime()       { return startPrime; }
            std::string getFileName()           { return fileName; }
    };
}

#endif
