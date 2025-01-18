#ifndef BUILD_RUNTIME_DATA_HPP
#define BUILD_RUNTIME_DATA_HPP

#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"
#include "ChangeCompressionLevel.hpp"
#include "ProjectFileIO.hpp"
#include "ProjectConstants.hpp"
#include "ProjectSemiConstants.hpp"
#include "SieveSegment.hpp"


// TODO change const std::span<const char>* to string or something
namespace InitData {
    void prepLevelChange(bool, std::size_t);

    void initForPrimesToBlocks(const std::span<const char>, const std::span<const char>*);
    void initForBlocksToBlocksHigher(const std::span<const char>, const std::span<const char>, std::size_t);
    void initForBlocksToBlocksLower(const std::span<const char>, const std::span<const char>, std::size_t);
    void initForPrimesToBlocks(const std::span<const char>*, const std::span<const char>);

    void initProgramData(const std::span<const char>, const std::span<const char>, std::size_t, std::size_t, std::size_t);
}

#endif
