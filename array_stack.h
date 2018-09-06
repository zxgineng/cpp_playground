#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <iostream>

template<typename T>
class ArrayStack {

public:
    explicit ArrayStack(int c = 10);

    ~ArrayStack();

    T top();  //栈顶

    int size();

    void push(T t);

    T pop();

private:
    int count;  //长度
    int capacity;  //容量
    T *array;  //底层数组
};

template<typename T>
ArrayStack<T>::ArrayStack(int c)
        :count(0), capacity(c), array(nullptr) {
    array = new T[capacity];
}

template<typename T>
ArrayStack<T>::~ArrayStack() {
    delete[] array;
}

template<typename T>
int ArrayStack<T>::size() {
    return count;
}

template<typename T>
void ArrayStack<T>::push(T t) {
    if (count != capacity) {
        array[count++] = t;
    }
}

template<typename T>
T ArrayStack<T>::pop() {
    if (count != 0) {
        return array[--count];
    }
}

template<typename T>
T ArrayStack<T>::top() {
    if (count != 0) {
        return array[count - 1];
    }
}
#endif
