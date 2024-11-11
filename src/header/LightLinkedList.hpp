#ifndef LIGHTLINKEDLIST_HPP
#define LIGHTLINKEDLIST_HPP

#include "LightListNode.hpp"
#include <mutex>

namespace protectedLinkedList {

class LinkedList {
public:
    LinkedList();
    void pushHead(Node *);
    Node *popHead();

    constexpr std::size_t size() {
        return N;
    }

private:
    std::mutex listMutex;
    Node head;
    std::size_t N;

}

}


#endif
