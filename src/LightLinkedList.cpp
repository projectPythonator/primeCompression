#include "header/LightLinkedList.hpp"
// update the namespaces properly
namespace protectedLinkedList {

LinkedList::LinkedList() {
    N = 0;
    head = nullptr;
}

void LinkedList::pushHead(Node *newHead) {
    newHead.setNext(this.head);
    this.head = newHead;
    this.size++;
}

Node *LinkedList::popHead() {
    Node * rHead = this.head;
    this.head = this.head.next;
    return rHead;
}

}
