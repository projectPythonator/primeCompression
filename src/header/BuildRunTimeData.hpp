#ifndef BUILD_RUNTIME_DATA_HPP
#define BUILD_RUNTIME_DATA_HPP

#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"
#include "ChangeLevelHigher.hpp"
#include "ChangeLevelLower.hpp"
#include "ProjectFileIO.hpp"
#include "ProjectConstants.hpp"
#include "ProjectSemiConstants.hpp"
#include "SieveSegment.hpp"


namespace InitData {
    void initProgramData(const std::span<const char>, const std::span<const char>, std::size_t, std::size_t);
}

#endif
