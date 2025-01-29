#ifndef INPUT_TO_DATA_HPP
#define INPUT_TO_DATA_HPP

#include "ContainerIncludes.hpp"
#include "FastMath.hpp"
#include "IntegralIncludes.hpp"
#include "ProjectContainers.hpp"
#include "ProjectConstants.hpp"
#include "ProjectFileIO.hpp"
#include "TestingIncludes.hpp"
    
namespace ProjectIO {


    class BytesToData {
        private:
            ProjectContainers::TaskData<std::uint8_t> byteData;
            ProjectContainers::TaskSizeInfo sizeData;
        public: 
            BytesToData(std::size_t bufSize, std::size_t lenSize): byteData(bufSize), sizeData(lenSize) {}

            std::size_t readRBX();

            /**
             * @brief Call to convert lower compression to higher compression.
             *
             * @param rb5Block  Block of rb5 compressed bytes.
             * @param rbxBlock  Block that will hold the resulting compression.
             *
             * @assumption      Both blocks are formatted and sized properly.   (not checked)
             * @assumption      dat is filled and sized properly.               (not checked)
             */
            std::size_t readText();
    };

    class BinaryToData {
        private:
            ProjectContainers::TaskData<std::uint64_t> binaryData;
        public: 
            BinaryToData(std::size_t bufSize): binaryData(bufSize) {}
                  
            /**
             * @brief Call to convert lower compression to higher compression.
             *
             * @param rb5Block  Block of rb5 compressed bytes.
             * @param rbxBlock  Block that will hold the resulting compression.
             *
             * @assumption      Both blocks are formatted and sized properly.   (not checked)
             * @assumption      dat is filled and sized properly.               (not checked)
             */
            std::size_t readBinary();
    };

}

#endif
