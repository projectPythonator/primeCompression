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

    /**
     * @brief Call to set up program based on cli arguments given.
     *
     * @param inName    String that holds the in file name [stdin default].
     * @param outName   String that holds the out file name [stdout default].
     * @param level     Number indicating the desired compression.
     * @param option    Number holding the io option. (need to create an enum).
     */
    void initProgramData(const std::span<const char>, const std::span<const char>, std::size_t, std::size_t);
}

#endif
