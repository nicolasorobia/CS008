#ifndef AVL_CPP
#define AVL_CPP

#include "avl.h"
#include <algorithm>

template<typename T>
int AVLTree<T>::_height (Node<T> *node) const
{
    if (node != nullptr) return node->height;

    return -1;
}

template<typename T>
int AVLTree<T>::_getBalance (Node<T> * node) const
{
    if (node != nullptr)
        return height(node->left) - height(node->right);
    
    return 0;
}




#endif