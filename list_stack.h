#ifndef LINKED_LIST_STACK_H
#define LINKED_LIST_STACK_H

#include <iostream>
#include "doubly_linked_list.h"

template<typename T>
class ListStack {

public:
    ListStack();

    ~ListStack();

    T top();  //栈顶

    int size();

    void push(T t);

    T pop();

private:
    DoublyLinkedList<T> *list;  //底层链表
};

template<typename T>
ListStack<T>::ListStack() {
    list = new DoublyLinkedList<int>();
}

template<typename T>
ListStack<T>::~ListStack() {
    delete list;
}

template<typename T>
int ListStack<T>::size() {
    return list->size();
}

template<typename T>
void ListStack<T>::push(T t) {
    list->insert(0,t);
};

template<typename T>
T ListStack<T>::pop() {
    return list->remove(0);
};

template<typename T>
T ListStack<T>::top() {
    return (*list)[0];
};
#endif
