#include <iostream>
#include <vector>
#include "singly_linked_list.h"
#include "doubly_linked_list.h"
#include "array_stack.h"
#include "list_stack.h"
#include "array_queue.h"
#include "list_queue.h"
#include "binary_search_tree.h"
#include "AVL_tree.h"
#include "hash_table.h"

using namespace std;

int main() {
    cout << "****测试单向链表****" << endl;
    SinglyLinkedList<int> l1;
    l1.push(0);
    l1.push(1);
    l1.push(3);
    l1.insert(2, 2);
    for (int x = 0; x < l1.size(); x++) {
        cout << dec << l1[x] << ",";
    }
    cout << endl;
    l1.remove(0);
    l1.pop();
    for (int x = 0; x < l1.size(); x++) {
        cout << dec << l1[x] << ",";
    }
    cout << endl;

    cout << endl;
    cout << "****测试双向链表****" << endl;
    DoublyLinkedList<int> l2;
    l2.push(0);
    l2.push(1);
    l2.push(3);
    l2.insert(2, 2);
    for (int x = 0; x < l2.size(); x++) {
        cout << dec << l2[x] << ",";
    }
    cout << endl;
    l2.remove(0);
    l2.pop();
    for (int x = 0; x < l2.size(); x++) {
        cout << dec << l2[x] << ",";
    }
    cout << endl;

    cout << endl;
    cout << "****测试数组栈****" << endl;
    ArrayStack<int> stack1;
    stack1.push(5);
    stack1.push(6);
    stack1.pop();
    cout << "栈的大小: " << stack1.size() << endl;
    cout << "栈顶元素: " << stack1.top() << endl;

    cout << endl;
    cout << "****测试链表栈****" << endl;
    ListStack<int> stack2;
    stack2.push(5);
    stack2.push(6);
    stack2.pop();
    cout << "栈的大小: " << stack2.size() << endl;
    cout << "栈顶元素: " << stack2.top() << endl;

    cout << endl;
    cout << "****测试数组队列****" << endl;
    ArrayQueue<int> queue1(5);
    queue1.push(5);
    queue1.push(6);
    queue1.pop();
    queue1.pop();
    queue1.push(7);
    queue1.push(8);
    queue1.push(5);
    queue1.push(6);
    cout << "队列大小: " << queue1.size() << endl;
    cout << "队列首元素: " << queue1.front() << endl;

    cout << endl;
    cout << "****测试链表队列****" << endl;
    ListQueue<int> queue2;
    queue2.push(5);
    queue2.push(6);
    queue2.pop();
    queue2.pop();
    queue2.push(7);
    queue2.push(8);
    queue2.push(5);
    queue2.push(6);
    cout << "队列大小: " << queue2.size() << endl;
    cout << "队列首元素: " << queue2.front() << endl;

    cout << endl;
    cout << "****测试查找二叉树****" << endl;
    BSTree<int> bstree;
    bstree.insert(62);
    bstree.insert(58);
    bstree.insert(47);
    bstree.insert(65);
    bstree.insert(60);
    bstree.insert(63);
    bstree.insert(66);
    bstree.insert(40);
    bstree.insert(70);
    bstree.remove(66);
    bstree.remove(47);
    bstree.remove(62);
    std::vector<int> vec = bstree.in_order();
    cout << "中序遍历：";
    for (int x:vec) {
        cout << x << ",";
    }
    cout << endl;
    cout << "最大值： " << bstree.max() << endl;
    cout << "最小值： " << bstree.min() << endl;

    cout << endl;
    cout << "****测试平衡二叉树****" << endl;
    AVLTree<int> avl_tree;
    avl_tree.insert(62);
    avl_tree.insert(58);
    avl_tree.insert(47);
    avl_tree.insert(65);
    avl_tree.insert(60);
    avl_tree.insert(63);
    avl_tree.insert(66);
    avl_tree.insert(40);
    avl_tree.insert(70);
    avl_tree.remove(66);
    avl_tree.remove(47);
    avl_tree.remove(62);
    cout << "中序遍历:" << endl;
    avl_tree.in_order();

    cout << endl;
    cout << "****测试哈希表****" << endl;
    HashTable<string, int> dict = HashTable<string, int>(50);
    dict.insert("a", 1);
    dict.insert("b", 2);
    dict.insert("c", 3);
    cout << "c为: " << dict["c"] << endl;
    dict.insert("c", 4);
    cout << "c为: " << dict["c"] << endl;
    int re = dict.remove("b");
    cout << "删除b: " << re << endl;

}

