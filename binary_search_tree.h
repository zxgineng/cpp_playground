#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <vector>

//结点
template<typename T>
class BSNode {
public:
    explicit BSNode(T t)
            : value(t), lchild(nullptr), rchild(nullptr) {}

    BSNode() = default;

    T value;
    BSNode<T> *lchild;
    BSNode<T> *rchild;
    BSNode<T> *parent;
};

//二叉查找树
template<typename T>
class BSTree {
public:
    BSTree();

    ~BSTree();

    std::vector<T> pre_order();    //前序遍历二叉树
    std::vector<T> in_order();        //中序遍历二叉树
    std::vector<T> post_order();    //后序遍历二叉树

    BSNode<T> *find(T key);        //迭代地进行查找

    T min(); //查找最小元素
    T max(); //查找最大元素

    BSNode<T> *successor(BSNode<T> *node);    //查找指定节点的后继节点
    BSNode<T> *predecessor(BSNode<T> *node);    //查找指定节点的前驱节点

    void insert(T key);    //插入指定值节点
    void remove(T key);    //删除指定值节点

private:
    BSNode<T> *root; //根节点
private:
    void pre_order(BSNode<T> *node, std::vector<T> &vec);

    void in_order(BSNode<T> *node, std::vector<T> &vec);

    void post_order(BSNode<T> *node, std::vector<T> &vec);

    void destory(BSNode<T> *&node);

};

template<typename T>
BSTree<T>::BSTree()
        :root(nullptr) {}

template<typename T>
BSTree<T>::~BSTree() {
    destory(root);
};

template<typename T>
void BSTree<T>::insert(T key) {
    BSNode<T> *parent_node = nullptr;  //保存父结点
    BSNode<T> *cur_node = root;  //保存当前结点


    while (cur_node != nullptr)  //往下遍历直到叶子结点
    {
        parent_node = cur_node;
        if (key > cur_node->value)
            cur_node = cur_node->rchild;
        else if (key < cur_node->value)
            cur_node = cur_node->lchild;
        else
            break;
    }

    cur_node = new BSNode<T>(key);
    if (parent_node == nullptr) {  //空树则为根
        root = cur_node;
    } else {
        if (key > parent_node->value) {
            parent_node->rchild = cur_node;
        } else
            parent_node->lchild = cur_node;
    }
    cur_node->parent = parent_node;

};

//查找
template<typename T>
BSNode<T> *BSTree<T>::find(T key) {
    BSNode<T> *cur_node = root;
    while (cur_node != nullptr) {
        if (key == cur_node->value)    //找到
            return cur_node;
        if (key > cur_node->value)        //关键字比节点值大，在节点右子树查找
            cur_node = cur_node->rchild;
        else
            cur_node = cur_node->lchild; //关键字比节点值小，在节点左子树查找
    }
    return nullptr;
}

//删除
template<typename T>
void BSTree<T>::remove(T key) {
    BSNode<T> *del_node = find(key);
    BSNode<T> *sub_node = nullptr;

    if (del_node == nullptr) return;
    if (del_node->lchild == nullptr || del_node->rchild == nullptr) {  //如果只有一个孩子或无孩子，直接用孩子替换删除结点
        if (del_node->lchild != nullptr) {  //直接使用删除结点的子结点来替代删除结点
            sub_node = del_node->lchild;
        } else {
            sub_node = del_node->rchild;
        }
    } else {  //如果有两个孩子，则使用前驱(后继)替换删除结点 前驱结点必然只有一个左孩子或无孩子
        sub_node = predecessor(del_node);
        if (sub_node->parent->lchild == sub_node) {  //将替换结点的父结点指向子结点
            sub_node->parent->lchild = sub_node->lchild;
        } else sub_node->parent->rchild = sub_node->lchild;
        sub_node->lchild = del_node->lchild;
        sub_node->rchild = del_node->rchild;
        if (del_node->lchild != nullptr)
            del_node->lchild->parent = sub_node;  //删除结点的左子结点指向替换节点，若前驱为删除节点的左子结点为前驱，则会出现空的情况
        del_node->rchild->parent = sub_node;  //删除结点的右子结点指向替换节点
    }

    if (sub_node != nullptr) {
        sub_node->parent = del_node->parent;  //对齐父结点
    }
    if (del_node->parent == nullptr) {  //如果删除结点为根结点
        root = sub_node;
    } else {  //删除结点的父结点指向替换结点
        if (del_node->parent->lchild == del_node) {
            del_node->parent->lchild = sub_node;
        } else del_node->parent->rchild = sub_node;
    }
    delete del_node;
}

//前驱 结点元素小于该结点元素并且值最大的结点
/*
1. 如果该结点有左子树，则该结点的前驱是其左子树中值最大的点
2. 如果没有左子树，若该结点是其父结点的右边孩子，那么该结点的前驱结点即为其父结点
3. 如果没有左子树，若该结点是其父结点的左边孩子，那么需要沿着其父结点一直向树的顶端寻找，直到找到一个结点P，P结点是其父结点的右边孩子
*/
template<typename T>
BSNode<T> *BSTree<T>::predecessor(BSNode<T> *node) {
    if (node->lchild != nullptr) {  //如果该结点有左子树，则该结点的前驱是其左子树中值最大的点
        node = node->lchild;  //进入左子树
        while (node->rchild != nullptr) {  //不断进入右子树，寻找最大值的点
            node = node->rchild;
        }
        return node;
    }

    BSNode<T> *parent_node = node->parent;  //如果该结点没有左子树，则判断该结点与其父结点的关系
    while (parent_node != nullptr && parent_node->lchild == node)//如果进入循环，则是第三种情况；否则为第二种情况
    {
        node = parent_node;
        parent_node = parent_node->parent;
    }
    return parent_node;
};

//后继 结点元素大于该结点元素并且值最小的结点
/*
1. 如果该结点有右子树，则该结点的前驱是其右子树中值最小的点
2. 如果没有右子树，若该结点是其父结点的左边孩子，那么该结点的前驱结点即为其父结点
3. 如果没有右子树，若该结点是其父结点的右边孩子，那么需要沿着其父结点一直向树的顶端寻找，直到找到一个结点P，P结点是其父结点的左边孩子
*/
template<typename T>
BSNode<T> *BSTree<T>::successor(BSNode<T> *node) {
    if (node->rchild != nullptr) {  //如果该结点有右子树，则该结点的前驱是其右子树中值最小的点
        node = node->rchild;  //进入右子树
        while (node->lchild != nullptr) {  //不断进入左子树，寻找最小值的点
            node = node->lchild;
        }
        return node;
    }

    BSNode<T> *parent_node = node->parent;  //如果该结点没有右子树，则判断该结点与其父结点的关系
    while (parent_node != nullptr && parent_node->rchild == node) {  //如果进入循环，则是第三种情况；否则为第二种情况
        node = parent_node;
        parent_node = parent_node->parent;
    }
    return parent_node;
};


//前序遍历
template<typename T>
std::vector<T> BSTree<T>::pre_order() {
    std::vector<T> vec;
    pre_order(root, vec);
    return vec;
};

template<typename T>
void BSTree<T>::pre_order(BSNode<T> *node, std::vector<T> &vec) {
    if (node != nullptr) {
        vec.push_back(node->value);
        pre_order(node->lchild, vec);
        pre_order(node->rchild, vec);
    }
};

/*中序遍历算法*/
template<typename T>
std::vector<T> BSTree<T>::in_order() {
    std::vector<T> vec(0);
    in_order(root, vec);
    return vec;
};

template<typename T>
void BSTree<T>::in_order(BSNode<T> *node, std::vector<T> &vec) {
    if (node != nullptr) {
        in_order(node->lchild, vec);
        vec.push_back(node->value);
        in_order(node->rchild, vec);
    }
};

/*后序遍历算法*/
template<typename T>
std::vector<T> BSTree<T>::post_order() {
    std::vector<T> vec;
    post_order(root, vec);
    return vec;
};

template<typename T>
void BSTree<T>::post_order(BSNode<T> *node, std::vector<T> &vec) {
    if (node != nullptr) {
        post_order(node->lchild, vec);
        post_order(node->rchild, vec);
        vec.push_back(node->value);
    }
};

template<typename T>
T BSTree<T>::min() {
    BSNode<T> *cur_node = root;
    if (cur_node != nullptr) {
        while (cur_node->lchild != nullptr) {
            cur_node = cur_node->lchild;
        }
        return cur_node->value;
    } else return 0;
}

template<typename T>
T BSTree<T>::max() {
    BSNode<T> *cur_node = root;
    if (cur_node != nullptr) {
        while (cur_node->rchild != nullptr) {
            cur_node = cur_node->rchild;
        }
        return cur_node->value;
    } else return 0;
}

template<typename T>
void BSTree<T>::destory(BSNode<T> *&node) {
    if (node != nullptr) {
        if (node->lchild != nullptr)
            destory(node->lchild);
        if (node->rchild != nullptr)
            destory(node->rchild);
        delete node;
        node = nullptr;
    }
};

#endif
