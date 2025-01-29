#ifndef PROJECT_CONTAINERS_HPP
#define PROJECT_CONTAINERS_HPP

#include "ContainerIncludes.hpp"
#include "IntegralIncludes.hpp"
#include "TestingIncludes.hpp"

namespace ProjectContainers {
    template <typename T>
    class TaskData {
        private:
            std::vector<T> tData;
            std::span<T> tSpan;
        public:
            TaskData(std::size_t dataSize): tData(dataSize), tSpan(tData) {}

            std::span<T> getSpan() const { return tSpan; }
            std::span<T> getSubspan(std::size_t beg, std::size_t siz) const { return tSpan.subspan(beg, siz); }

            void setSpan(std::size_t beg, std::size_t siz)  { tSpan = getSubspan(beg, siz); }
            void resetSpan() { tSpan = std::span(tData); }
    };

    class TaskSizeInfo {
        private:
            std::size_t infoAmount;
            std::vector<std::size_t> infoData;
            std::span<std::size_t> infoSpan;
        public:
            TaskSizeInfo(std::size_t dataSize): infoAmount{0}, infoData(dataSize), infoSpan(infoData) {}

            std::span<std::size_t> getSubspan(std::size_t beg, std::size_t siz) const { 
                return infoSpan.subspan(beg, siz); 
            }
            std::span<std::size_t> getSpan() const { return infoSpan; }
            std::size_t getAmount() const { return infoAmount; }

            void setAmount(std::size_t amt) { infoAmount = amt; }
            void setSpan(std::size_t beg, std::size_t siz) { infoSpan = getSubspan(beg, siz); }
            void resetSpan() { infoSpan = std::span(infoData); }
    };
}
#endif
