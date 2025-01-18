#ifndef BUILD_RUNTIME_DATA_HPP
#define BUILD_RUNTIME_DATA_HPP

#include "BuildRunTimeData.hpp"
#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"
#include "ChangeCompressionLevel.hpp"
#include "ProjectFileIO.hpp"
#include "ProjectConstants.hpp"
#include "ProjectSemiConstants.hpp"


// TODO change const char * to string or something
namespace InitData {
    void prepLevelChange(bool, std::size_t);

    void initForPrimesToBlocks(const char *, const char *);
    void initForBlocksToBlocksHigher(const char * , const char *, std::size_t);
    void initForBlocksToBlocksLower(const char * , const char *, std::size_t);
    void initForPrimesToBlocks(const char *, const char *);

    void initProgramData(const char *, const char *, std::size_t, std::size_t, std::size_t);
}

#endif
