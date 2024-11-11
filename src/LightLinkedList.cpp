#include "header/LightLinkedList.hpp"

namespace protectedLinkedList {

LinkedList::LinkedList() {
    N = 0;
    head = nullptr;
}

void LinkedList::pushHead(Node *newHead) {
    this.listMutex.lock();
    newHead.setNext(this.head);
    this.head = newHead;
    this.size++;
    this.listMutex.unlock();
}

Node *LinkedList::popHead() {
    Node * rHead = this.head;
    this.head = this.head.next;
    return rHead;
}
}
