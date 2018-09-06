#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>

template<typename T>
struct AVLNode {
    AVLNode(T value, AVLNode<T> *l, AVLNode<T> *r)
            : key(value), lchild(l), rchild(r) {}

    T key;
    int height;
    AVLNode<T> *lchild;
    AVLNode<T> *rchild;
};

template<typename T>
class AVLTree {
public:
    AVLTree();            //构造函数
    ~AVLTree();            //析构函数

    void pre_order();    //前序遍历AVL树
    void in_order();        //中序遍历AVL树	
    void post_order();    //后序遍历AVL树

    void insert(T key);    //插入指定值的节点
    void remove(T key);    //移除指定值的节点

    AVLNode<T> *search_recurse(T key);    //利用递归算法进行指定值的查找
    AVLNode<T> *search_iterator(T key);    //利用迭代算法进行指定值的查找
    T minimum();        //返回AVL中的最小值
    T maximum();        //返回AVL中的最大值

    int height();        //返回树的高度

private:
    AVLNode<T> *root;    //AVL树的根节点

private:
    void pre_order(AVLNode<T> *pnode) const;

    void in_order(AVLNode<T> *pnode) const;

    void post_order(AVLNode<T> *pnode) const;

    void destory(AVLNode<T> *&pnode);

    int height(AVLNode<T> *pnode);

    int max(int a, int b);

    AVLNode<T> *insert(AVLNode<T> *&pnode, T key);

    AVLNode<T> *remove(AVLNode<T> *&pnode, T key); //删除AVL树中节点pdel，并返回被删除的节点

    AVLNode<T> *minimum(AVLNode<T> *pnode) const;

    AVLNode<T> *maximum(AVLNode<T> *pnode) const;

    AVLNode<T> *search_recurse(AVLNode<T> *pnode, T key) const;

    AVLNode<T> *search_iterator(AVLNode<T> *pnode, T key) const;

    AVLNode<T> *leftRotation(AVLNode<T> *pnode);        //单旋:左旋操作
    AVLNode<T> *rightRotation(AVLNode<T> *pnode);        //单旋:右旋操作
    AVLNode<T> *leftRightRotation(AVLNode<T> *pnode);    //双旋:先左旋后右旋操作
    AVLNode<T> *rightLeftRotation(AVLNode<T> *pnode);    //双旋:先右旋后左旋操作

};

/*构造函数*/
template<typename T>
AVLTree<T>::AVLTree()
        :root(nullptr) {};

/*析构函数*/
template<typename T>
AVLTree<T>::~AVLTree() {
    destory(root);
}

/*返回两者中的较大者*/
template<typename T>
int AVLTree<T>::max(int a, int b) {
    return a > b ? a : b;
};

/*返回树中最大节点值*/
template<typename T>
AVLNode<T> *AVLTree<T>::maximum(AVLNode<T> *pnode) const {
    if (pnode != nullptr) {
        while (pnode->rchild != nullptr)
            pnode = pnode->rchild;
        return pnode;
    }
    return nullptr;
};

template<typename T>
T AVLTree<T>::maximum() {
    AVLNode<T> *presult = maximum(root);
    if (presult != nullptr)
        return presult->key;
};

/*返回树中最小节点值*/
template<typename T>
AVLNode<T> *AVLTree<T>::minimum(AVLNode<T> *pnode) const {
    if (pnode != nullptr) {
        while (pnode->lchild != nullptr)
            pnode = pnode->lchild;
        return pnode;
    }
    return nullptr;
};

template<typename T>
T AVLTree<T>::minimum() {
    AVLNode<T> *presult = minimum(root);
    if (presult != nullptr)
        return presult->key;
};

/*返回一棵树的高度*/
template<typename T>
int AVLTree<T>::height(AVLNode<T> *pnode) {
    if (pnode != nullptr) {
        return pnode->height;
    }
    return 0;                                                                //如果是空树，高度为0
};

template<typename T>
int AVLTree<T>::height() {
    return height(root);
};

/*左旋转操作*/
/*pnode为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template<typename T>
AVLNode<T> *AVLTree<T>::leftRotation(AVLNode<T> *proot) {
    AVLNode<T> *prchild = proot->rchild;
    proot->rchild = prchild->lchild;
    prchild->lchild = proot;

    proot->height = max(height(proot->lchild), height(proot->rchild)) + 1;     //更新节点的高度值
    prchild->height = max(height(prchild->lchild), height(prchild->rchild)) + 1; //更新节点的高度值

    return prchild;
};

/*右旋转操作*/
/*pnode为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template<typename T>
AVLNode<T> *AVLTree<T>::rightRotation(AVLNode<T> *proot) {
    AVLNode<T> *plchild = proot->lchild;
    proot->lchild = plchild->rchild;
    plchild->rchild = proot;

    proot->height = max(height(proot->lchild), height(proot->rchild)) + 1;     //更新节点的高度值
    plchild->height = max(height(plchild->lchild), height(plchild->rchild)) + 1; //更新节点的高度值

    return plchild;
};

/*先左后右做旋转*/
/*参数proot为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template<typename T>
AVLNode<T> *AVLTree<T>::leftRightRotation(AVLNode<T> *proot) {
    proot->lchild = leftRotation(proot->lchild);
    return rightRotation(proot);
};
/*先右旋再左旋*/
/*参数proot为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template<typename T>
AVLNode<T> *AVLTree<T>::rightLeftRotation(AVLNode<T> *proot) {
    proot->rchild = rightRotation(proot->rchild);
    return leftRotation(proot);
};

/*插入操作*/
/*递归地进行插入*/
/*返回插入后的根节点*/
template<typename T>
AVLNode<T> *AVLTree<T>::insert(AVLNode<T> *&pnode, T key) {
    if (pnode == nullptr)    //寻找到插入的位置
    {
        pnode = new AVLNode<T>(key, nullptr, nullptr);
    } else if (key > pnode->key)    //插入值比当前结点值大，插入到当前结点的右子树上
    {
        pnode->rchild = insert(pnode->rchild, key);
        if (height(pnode->rchild) - height(pnode->lchild) == 2) //插入后出现失衡
        {
            if (key > pnode->rchild->key) //情况一：插入右子树的右节点，进行左旋
                pnode = leftRotation(pnode);
            else if (key < pnode->rchild->key)  //情况三：插入右子树的左节点,进行先右再左旋转
                pnode = rightLeftRotation(pnode);
        }
    } else if (key < pnode->key) //插入值比当前节点值小，插入到当前结点的左子树上
    {
        pnode->lchild = insert(pnode->lchild, key);
        if (height(pnode->lchild) - height(pnode->rchild) == 2) //如果插入导致失衡
        {
            if (key < pnode->lchild->key)        //情况二：插入到左子树的左孩子节点上，进行右旋
                pnode = rightRotation(pnode);
            else if (key > pnode->lchild->key)
                pnode = leftRightRotation(pnode);//情况四：插入到左子树的右孩子节点上，进行先左后右旋转
        }
    }
    pnode->height = max(height(pnode->lchild), height(pnode->rchild)) + 1;
    return pnode;
};

template<typename T>
void AVLTree<T>::insert(T key) {
    insert(root, key);
};


/*递归查找指定元素*/
template<typename T>
AVLNode<T> *AVLTree<T>::search_recurse(T key) {
    return search_recurse(root, key);
};

template<typename T>
AVLNode<T> *AVLTree<T>::search_recurse(AVLNode<T> *pnode, T key) const {
    if (pnode != nullptr) {
        if (key == pnode->key)
            return pnode;
        if (key > pnode->key)
            return search_recurse(pnode->rchild, key);
        else
            return search_recurse(pnode->lchild, key);
    }
    return nullptr;
};

/*非递归查找指定元素*/
template<typename T>
AVLNode<T> *AVLTree<T>::search_iterator(T key) {
    return search_iterator(root, key);
};

template<typename T>
AVLNode<T> *AVLTree<T>::search_iterator(AVLNode<T> *pnode, T key) const {
    while (pnode != nullptr) {
        if (pnode->key == key)
            return pnode;
        else if (key > pnode->key)
            pnode = pnode->rchild;
        else
            pnode = pnode->lchild;
    }
    return nullptr;
};


/*删除指定元素*/
template<typename T>
AVLNode<T> *AVLTree<T>::remove(AVLNode<T> *&pnode, T key) {
    if (pnode != nullptr) {
        if (key == pnode->key)            //找到删除的节点
        {
            //因AVL也是二叉排序树，删除节点要维护其二叉排序树的条件
            if (pnode->lchild != nullptr && pnode->rchild != nullptr)        //若左右都不为空
            {
                if (height(pnode->lchild) > height(pnode->rchild))        //左子树比右子树高
                {
                    //使用左子树最大节点来代替被删节点，而删除该最大节点
                    AVLNode<T> *ppre = maximum(pnode->lchild);        //左子树最大节点
                    pnode->key = ppre->key;                                //将最大节点的值覆盖当前结点
                    pnode->lchild = remove(pnode->lchild, ppre->key);    //递归地删除最大节点
                } else {
                    //使用最小节点来代替被删节点，而删除该最小节点
                    AVLNode<T> *psuc = minimum(pnode->rchild);        //右子树的最小节点
                    pnode->key = psuc->key;                                //将最小节点值覆盖当前结点
                    pnode->rchild = remove(pnode->rchild, psuc->key);    //递归地删除最小节点
                }

            } else {
                AVLNode<T> *ptemp = pnode;
                if (pnode->lchild != nullptr)
                    pnode = pnode->lchild;
                else if (pnode->rchild != nullptr)
                    pnode = pnode->rchild;
                delete ptemp;
                return nullptr;
            }

        } else if (key > pnode->key)        //要删除的节点比当前节点大，则在右子树进行删除
        {
            pnode->rchild = remove(pnode->rchild, key);
            if (height(pnode->lchild) - height(pnode->rchild) == 2) //删除右子树节点导致不平衡:相当于情况二或情况四
            {
                if (height(pnode->lchild->rchild) > height(pnode->lchild->lchild))
                    pnode = leftRightRotation(pnode);                //相当于情况四
                else
                    pnode = rightRotation(pnode);                    //相当于情况二
            }
        } else if (key < pnode->key)        //要删除的节点比当前节点小，则在左子树进行删除
        {
            pnode->lchild = remove(pnode->lchild, key);
            if (height(pnode->rchild) - height(pnode->lchild) == 2)  //删除左子树节点导致不平衡：相当于情况三或情况一
            {
                if (height(pnode->rchild->lchild) > height(pnode->rchild->rchild))
                    pnode = rightLeftRotation(pnode);
                else
                    pnode = leftRotation(pnode);
            }
        }
        return pnode;
    }
    return nullptr;
};

template<typename T>
void AVLTree<T>::remove(T key) {
    root = remove(root, key);
};

/*中序遍历*/
template<typename T>
void AVLTree<T>::in_order(AVLNode<T> *pnode) const {
    if (pnode != nullptr) {
        in_order(pnode->lchild);
        std::cout << pnode->key << std::endl;
        in_order(pnode->rchild);
    }
};

template<typename T>
void AVLTree<T>::in_order() {
    in_order(root);
};

/*前序遍历*/
template<typename T>
void AVLTree<T>::pre_order(AVLNode<T> *pnode) const {
    if (pnode != nullptr) {
        std::cout << pnode->key << std::endl;
        in_order(pnode->lchild);
        in_order(pnode->rchild);
    }
};

template<typename T>
void AVLTree<T>::pre_order() {
    pre_order(root);
};

/*后列遍历*/
template<typename T>
void AVLTree<T>::post_order(AVLNode<T> *pnode) const {
    if (pnode != nullptr) {
        in_order(pnode->lchild);
        in_order(pnode->rchild);
        std::cout << pnode->key << std::endl;
    }
}

template<typename T>
void AVLTree<T>::post_order() {
    post_order(root);
};


/*销毁AVL树*/
template<typename T>
void AVLTree<T>::destory(AVLNode<T> *&pnode) {
    if (pnode != nullptr) {
        destory(pnode->lchild);
        destory(pnode->rchild);
        delete pnode;
        pnode = nullptr;
    }
};

#endif
