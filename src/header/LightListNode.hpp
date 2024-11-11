#ifndef LIGHTLISTNODE_HPP
#define LIGHTLISTNODE_HPP

#include <cinttypes>

namespace pseudoConstNode {

struct Node {
    Node *next = nullptr;
    std::uint32_t primeIndex = 0;
    void setNext(Node *newNext) {
        next = newNext;
    }
};

}

#endif
