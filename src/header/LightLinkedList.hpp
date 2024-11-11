#ifndef LIGHTLINKEDLIST_HPP
#define LIGHTLINKEDLIST_HPP

#include <mutex>

namespace protectedLinkedList {

struct Node {
    Node *next;
    std::uint32_t primeIndex;
};

class LinkedList {
public:
    LinkedList();
    void addNode(Node *);
    void resetHead();

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
