#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include "ContainerIncludes.hpp"
#include "IntegralTypeIncludes.hpp"

// TODO add includes to the other classes
// TODO change this to class based
// TODO might need to fix the 
namespace ArrayList {
    // I think this is the c++ version of extend in python
    void extendNodeList(std::size_t);
    void buildNodeList(std::size_t);

    void setNodeNext(uint32_t, uint32_t);
    uint32_t getNodeNext(uint32_t);
}

#endif
