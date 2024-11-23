#include "header/ArrayList.hpp"

namespace {
    std::vector<uint32_t> array_list;
}

// TODO potentially create class
namespace ArrayList {
    // I think this is the c++ version of extend in python
    void extendNodeList(std::size_t listSize) {
        array_list.resize(array_list.size() + listSize, list_end);
    }

    void buildNodeList(std::size_t listSize) {
        array_list.assign(listSize, list_end);
    }
    
    void setNodeNext(uint32_t node, uint32_t newNode) {
        array_list[node] = newNode;
    }

    uint32_t getNodeNext(uint32_t node) {
        return array_list[node];
    }
}
