#ifndef LIGHTLINKEDLIST_HPP
#define LIGHTLINKEDLIST_HPP

#include "LightListNode.hpp"

namespace protectedLinkedList {

class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    void pushHead(Node *);
    Node *popHead();

    constexpr std::size_t size() {
        return N;
    }

private:
    Node *head;
    std::size_t N;
};

}


#endif
