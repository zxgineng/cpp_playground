#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>

template<typename Tkey, typename Tvalue>
class HashNode {

public:
    HashNode() = default;

    HashNode(Tkey key, Tvalue value, HashNode<Tkey, Tvalue> *next)
            : key(key), value(value), next(next) {}

public:
    Tkey key;
    Tvalue value;
    HashNode<Tkey, Tvalue> *next;
};

template<typename Tkey, typename Tvalue>
class HashTable {
private:
    HashNode<Tkey, Tvalue> *table;
    int size;
public:
    explicit HashTable(int size);

    ~HashTable();

    void insert(Tkey key, Tvalue value);

    Tvalue remove(Tkey key);

    Tvalue operator[](Tkey key);  //获取值

private:
    int hash_index(Tkey key);
};

template<typename Tkey, typename Tvalue>
HashTable<Tkey, Tvalue>::HashTable(int size)
        :size(size), table(nullptr) {
    table = new HashNode<Tkey, Tvalue>[size]();
}

template<typename Tkey, typename Tvalue>
HashTable<Tkey, Tvalue>::~HashTable() {
    delete[] table;
}

template<typename Tkey, typename Tvalue>
int HashTable<Tkey, Tvalue>::hash_index(Tkey key) {
    std::hash<Tkey> h;
    int index = h(key) % size;
    return index;
}


template<typename Tkey, typename Tvalue>
void HashTable<Tkey, Tvalue>::insert(Tkey key, Tvalue value) {
    int index = hash_index(key);
    HashNode<Tkey, Tvalue> *cur_node = table + index;
    while (cur_node->next != nullptr) {
        cur_node = cur_node->next;
        if (cur_node->key == key) {  //如果已经存在key
            cur_node->value = value;
            return;
        }
    }
    auto *new_node = new HashNode<Tkey, Tvalue>(key, value, nullptr);
    cur_node->next = new_node;
}

template<typename Tkey, typename Tvalue>
Tvalue HashTable<Tkey, Tvalue>::remove(Tkey key) {
    int index = hash_index(key);
    HashNode<Tkey, Tvalue> *cur_node = table + index;
    HashNode<Tkey, Tvalue> *parent_node = nullptr;
    while (cur_node->next != nullptr) {
        parent_node = cur_node;
        cur_node = cur_node->next;
        if (cur_node->key == key) {
            parent_node->next = cur_node->next;
            Tvalue temp = cur_node->value;
            delete cur_node;
            return temp;
        }
    }
    exit(1);
}

template<typename Tkey, typename Tvalue>
Tvalue HashTable<Tkey, Tvalue>::operator[](Tkey key) {
    int index = hash_index(key);
    HashNode<Tkey, Tvalue> *cur_node = table + index;
    while (cur_node->next != nullptr) {
        cur_node = cur_node->next;
        if (cur_node->key == key) {
            return cur_node->value;
        }
    }
    exit(1);
}

#endif
