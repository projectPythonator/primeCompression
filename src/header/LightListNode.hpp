#ifndef LIGHTLISTNODE_HPP
#define LIGHTLISTNODE_HPP

#include <cinttypes>

namespace pseudoConstNode {
// do I need to add an initializer func or turn this into 
struct Node {
    Node *nextNode = nullptr; 
    std::uint32_t primeIndex = 0;
    void setNext(Node *newNext) {
        nextNode = newNext;
    }
};

}

#endif
