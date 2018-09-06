#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include <iostream>

template<typename T>
class ArrayQueue {
public:
    explicit ArrayQueue(int c = 10);

    ~ArrayQueue();

public:
    int size();            //队列的大小
    void push(T t);        //入队列
    T pop();            //出队列
    T front();            //队首元素

private:
    int capacity;  //容量
    int begin;  //队首下标
    int end;  //队尾下标
    T *array;  //底层数组
};

template<typename T>
ArrayQueue<T>::ArrayQueue(int c)
        : capacity(c), begin(0), end(0), array(nullptr) {
    array = new T[capacity]{};
}

template<typename T>
ArrayQueue<T>::~ArrayQueue() {
    delete[] array;
}

template<typename T>
int ArrayQueue<T>::size() {
    return (end - begin + capacity) % capacity; //计算队列长度
}

template<typename T>
void ArrayQueue<T>::push(T t) {
    if (end + 1 % capacity == begin) exit(1);  //判断队列是否已满
    array[end] = t;
    end = (end + 1) % capacity;
}

template<typename T>
T ArrayQueue<T>::pop() {
    if (end == begin) exit(1);  //判断队列是否为空
    T temp = array[begin];
    begin = (begin + 1) % capacity;
    return temp;
}

template<typename T>
T ArrayQueue<T>::front() {
    if (end == begin) exit(1);   //判断队列是否为空
    return array[begin];
}

#endif
