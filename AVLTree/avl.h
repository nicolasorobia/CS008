#ifndef AVL_H
#define AVL_H

#include "node.h"

template<typename T>
class AVLTree
{
private:
    Node<T> *root = nullptr;
    int _size     = 0;

    int _height     (Node<T> *node) const; // return height of node, checking for nullptr
    int _getBalance (Node<T> *node) const; // return node's balance factor


public:
    AVLTree() = default;

    int size()   const { return _size; }
    int height() const { return _height(root); }


    // Big 3
    ~AVLTree();
    AVLTree(const AVLTree<T>& tree);
    AVLTree<T>& operator=(const AVLTree<T>& tree);


};



#endif