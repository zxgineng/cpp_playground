# ifndef SINGLY_LINKED_LIST_H
# define SINGLY_LINKED_LIST_H

#include <iostream>

//结点
template<typename T>
class SingleNode {
public :
    T value;
    SingleNode<T> *next;
public:
    SingleNode() = default;

    SingleNode(T value, SingleNode<T> *next)
            : value(value), next(next) {}
};

//单向链表
template<typename T>
class SinglyLinkedList {

public:
    SinglyLinkedList();

    ~SinglyLinkedList();

    int size();  //长度
    void push(T t);  //在最后添加值
    T pop();  //删除最后一个值
    void insert(int index, T t); //插入
    T remove(int index);  //删除
    T operator[](int index);  //获取值

private :
    int count;  //链表长度
    SingleNode<T> *head;  //头指针

private :
    SingleNode<T> *get_node(int index);  //获取结点
};

//构造函数
template<typename T>
SinglyLinkedList<T>::SinglyLinkedList()
        :count(0), head(nullptr) {
    //创建头结点
    head = new SingleNode<T>(0, nullptr);
}

//析构函数
template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    SingleNode<T> *node = head;
    while (nullptr != node) {
        SingleNode<T> *temp = node;
        node = node->next;
        delete temp;
    }
};

//在最后添加元素
template<typename T>
void SinglyLinkedList<T>::push(T t) {
    SingleNode<T> *last_node = get_node(count - 1);
    auto *new_node = new SingleNode<T>(t, nullptr);
    last_node->next = new_node;
    count++;
}

//删除最后的元素
template<typename T>
T SinglyLinkedList<T>::pop() {
    SingleNode<T> *new_last_node = get_node(count - 2);
    SingleNode<T> *del_node = new_last_node->next;
    new_last_node->next = nullptr;
    count--;
    T temp = del_node->value;
    delete del_node;
    return temp;
}

//取结点
template<typename T>
SingleNode<T> *SinglyLinkedList<T>::get_node(int index) {
    if (index >= count || index < -1)
        exit(139);
    int temp = 0;
    SingleNode<T> *cur_node = head;
    while (temp <= index) {
        cur_node = cur_node->next;
        temp++;
    }
    return cur_node;
}

//取值
template<typename T>
T SinglyLinkedList<T>::operator[](int index) {
    SingleNode<T> *node = get_node(index);
    return node->value;
}

//长度
template<typename T>
int SinglyLinkedList<T>::size() {
    return count;
};

//插入值
template<typename T>
void SinglyLinkedList<T>::insert(int index, T t) {
    SingleNode<T> *pre_node = get_node(index - 1);
    auto *new_node = new SingleNode<T>(t, pre_node->next); //新结点next指向原来的结点
    pre_node->next = new_node;  //上个结点指向新结点
    count++;
};

//删除值
template<typename T>
T SinglyLinkedList<T>::remove(int index) {
    if (index >= count || index < 0)
        exit(139);
    SingleNode<T> *pre_node = get_node(index - 1);
    SingleNode<T> *del_node = pre_node->next;
    pre_node->next = del_node->next;  //将删除结点的前后结点相连
    count--;
    T temp = del_node->value;  //保存返回值
    delete del_node;
    return temp;
};


# endif