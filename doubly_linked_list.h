# ifndef DOUBLY_LINKED_LIST_H
# define DOUBLY_LINKED_LIST_H

#include <iostream>

//结点
template<typename T>
class DoubleNode {
public :
    T value;
    DoubleNode<T> *next;
    DoubleNode<T> *prev;

public:
    DoubleNode() = default;

    DoubleNode(T value, DoubleNode<T> *prev, DoubleNode<T> *next)
            : value(value), next(next), prev(prev) {}
};

//双向链表
template<typename T>
class DoublyLinkedList {

public:
    DoublyLinkedList();

    ~DoublyLinkedList();

    int size();  //长度
    void push(T t);  //在最后添加值
    T pop();  //删除最后一个值
    void insert(int index, T t); //插入
    T remove(int index);  //删除
    T operator[](int index);  //获取值

private :
    int count;  //链表长度
    DoubleNode<T> *head;  //头指针

private :
    DoubleNode<T> *get_node(int index);  //获取结点
};

//构造函数
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList()
        :count(0), head(nullptr) {
    //创建头结点
    head = new DoubleNode<T>(0, nullptr, nullptr);
    head->prev = head;  //首尾相连
    head->next = head;
}

//析构函数
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    DoubleNode<T> *node = head;
    while (count>=0) {
        node = node->next;
        delete node->prev;
        count--;
    }
};

//在最后添加元素
template<typename T>
void DoublyLinkedList<T>::push(T t) {
    DoubleNode<T> *last_node = get_node(count - 1);
    auto *new_node = new DoubleNode<T>(t,last_node,head);
    last_node->next = new_node;  //旧末结点next指向新节点
    head->prev = new_node;  //头结点prev指向新节点
    count++;
}

//删除最后的元素
template<typename T>
T DoublyLinkedList<T>::pop() {
    DoubleNode<T> *del_node = get_node(count - 1);
    del_node->prev->next = head;  //上一结点next指向头结点
    head->prev = del_node->prev;  //头结点prev指向上一结点
    count--;
    T temp = del_node->value;
    delete del_node;
    return temp;
}

//取结点
template<typename T>
DoubleNode<T> *DoublyLinkedList<T>::get_node(int index) {
    if (index >= count || index < -1)
        exit(139);
    if (index==-1) return head;
    DoubleNode<T> *cur_node = head;
    if (index < count / 2) {  //从前向后遍历
        while (index >= 0) {
            cur_node = cur_node->next;
            index--;
        }
    } else {  //从后向前遍历
        index = count - index;
        while (index > 0) {
            cur_node = cur_node->prev;
            index--;
        }
    }
    return cur_node;
}

//取值
template<typename T>
T DoublyLinkedList<T>::operator[](int index) {
    DoubleNode<T> *node = get_node(index);
    return node->value;
}

//长度
template<typename T>
int DoublyLinkedList<T>::size() {
    return count;
};

//插入值
template<typename T>
void DoublyLinkedList<T>::insert(int index, T t) {
    DoubleNode<T> *pre_node = get_node(index-1);
    auto *new_node = new DoubleNode<T>(t,  pre_node,pre_node->next);
    pre_node->next->prev = new_node;
    pre_node->next = new_node;
    count++;
};

//删除值
template<typename T>
T DoublyLinkedList<T>::remove(int index) {
    DoubleNode<T> *del_node = get_node(index);
    del_node->prev->next = del_node->next;
    del_node->next->prev = del_node->prev;
    count--;
    T temp = del_node->value;
    delete del_node;
    return temp;
};


# endif