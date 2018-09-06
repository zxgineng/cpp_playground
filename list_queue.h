#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include <iostream>
#include "doubly_linked_list.h"

template<typename T>
class ListQueue {
public:
    ListQueue();

    ~ListQueue();

public:
    int size();            //队列的大小
    void push(T t);        //入队列
    T pop();            //出队列
    T front();            //队首元素

private:
    DoublyLinkedList<T> *list;  //底层数组
};

template<typename T>
ListQueue<T>::ListQueue()
        : list(nullptr) {
    list = new DoublyLinkedList<int>();
}

template<typename T>
ListQueue<T>::~ListQueue() {
    delete list;
}

template<typename T>
int ListQueue<T>::size() {
    return list->size(); //计算队列长度
}

template<typename T>
void ListQueue<T>::push(T t) {
    list->push(t);  //在链表尾部入队
}

template<typename T>
T ListQueue<T>::pop() {
    return list->remove(0);  //在链表头部出队
}

template<typename T>
T ListQueue<T>::front() {
    return (*list)[0];  //链表头部为队首
}


#endif
