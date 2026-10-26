#ifndef AVL_CPP
#define AVL_CPP

#include "avl.h"
#include <algorithm>
#include <iostream>

/*
    ---------- PRIVATE FUNCTIONS ----------
*/

template <typename T>
int AVL<T>::_height(Node<T> *node) const
{
    if (node != nullptr) return node->height;

    // -1 for nullptr (a leaf is 0)
    return -1;
}

template <typename T>
int AVL<T>::_getBF(Node<T> *node) const
{
    if (node != nullptr)
        return _height(node->left) - _height(node->right);
    
    return 0;
}

template <typename T>
void AVL<T>::_updateHeight(Node<T> *node)
{
    node->height = std::max(_height(node->left), _height(node->right)) + 1;
}

/*  Right rotation at node:

          node                 newRoot
          /  \                  /   \
     newRoot  C      -->       A     node
        /   \                        /   \
      A   subtree                subtree  C
*/

template <typename T>
void AVL<T>::_rotateRight(Node<T> *&node)
{
    Node<T> *newRoot = node->left;
    Node<T> *subtree = newRoot->right;

    newRoot->right = node;
    node->left = subtree;

    // update heights
    _updateHeight(node);
    _updateHeight(newRoot);

    node = newRoot;
}

/*  Left rotation at node:

      node                      newRoot
     /   \                       /   \
    A    newRoot      -->     node    C
          /   \               /   \
       subtree  C            A   subtree
*/

template <typename T>
void AVL<T>::_rotateLeft(Node<T> *&node)
{
    Node<T> *newRoot = node->right;
    Node<T> *subtree = newRoot->left;

    newRoot->left = node;
    node->right = subtree;

    _updateHeight(node);
    _updateHeight(newRoot);

    node = newRoot;
}

template <typename T>
void AVL<T>::_rebalance(Node<T> *&node)
{
    // update height and get balance factor first
    _updateHeight(node);
    int balance = _getBF(node);

    // check balance cases and rotate
    if (balance > 1 && _getBF(node->left) >= 0)        // LL case
        _rotateRight(node);
    else if (balance > 1 && _getBF(node->left) < 0)    // LR case
    {
        _rotateLeft(node->left);
        _rotateRight(node);
    }

    else if (balance < -1 && _getBF(node->right) <= 0) // RR case
        _rotateLeft(node);
    else if (balance < - 1 && _getBF(node->right) > 0) // RL case
    {
        _rotateRight(node->right);
        _rotateLeft(node);
    }
}

template <typename T>
void AVL<T>::_push(Node<T> *&node, const T& data)
{
    // empty spot, push here
    if (node == nullptr) {
        node = new Node<T>(data);
        return;
    }

    // duplicate: return early
    if (data == node->data) return;

    if (data < node->data)
        _push(node->left, data);
    else
        _push(node->right, data);

    _rebalance(node);
}

template <typename T>
Node<T>* AVL<T>::findPredecessor(Node<T> *node)
{
    if (node->right == nullptr) return node;
    return findPredecessor(node->right);
}

template <typename T>
void AVL<T>::_remove(Node<T> *&node, const T& data)
{
    // empty, remove nothing
    if (node == nullptr) return;

    if (data < node->data)
        _remove(node->left, data);
    else if (data > node->data)
        _remove(node->right, data);
    else
    {
        if (node->left == nullptr) {
            Node<T> *temp = node->right;
            delete node;
            node = temp;
            return;
        }

        if (node->right == nullptr) {
            Node<T> *temp = node->left;
            delete node;
            node = temp;
            return;
        }

        Node<T> *pred = findPredecessor(node->left);
        node->data = pred->data;
        _remove(node->left, pred->data);
    }

    _rebalance(node);
}

template <typename T>
void AVL<T>::_clear(Node<T> *node)
{
    if (node == nullptr) return;

    _clear(node->left);
    _clear(node->right);
    delete node;
}

template <typename T>
Node<T>* AVL<T>::_copy(Node<T> *node) const
{
    if (node == nullptr) return nullptr;

    Node<T> *temp = new Node<T>(node->data);
    temp->left = _copy(node->left);
    temp->right = _copy(node->right);

    return temp;
}

template <typename T>
void AVL<T>::_preorder(Node<T> *node, void (*f)(T&)) const
{
    if (node == nullptr) return;
    f(node->data);
    _preorder(node->left, f);
    _preorder(node->right, f);
}

template <typename T>
void AVL<T>::_inorder(Node<T> *node, void (*f)(T&)) const
{
    if (node == nullptr) return;
    
    _inorder(node->left, f);
    f(node->data);
    _inorder(node->right, f);
}

template <typename T>
void AVL<T>::_postorder(Node<T> *node, void (*f)(T&)) const
{
    if (node == nullptr) return;

    _postorder(node->left, f);
    _postorder(node->right, f);
    f(node->data);
}

/*
    -----------------------------------------------------------------------------
*/

/*
    ---------- PUBLIC FUNCTIONS ----------
*/

template <typename T>
void AVL<T>::traverse(Traversal order, void (*f)(T&)) const
{
    switch(order)
    {
        case Traversal::Preorder:  _preorder(root, f);  break;
        case Traversal::Inorder:   _inorder(root, f);   break;
        case Traversal::Postorder: _postorder(root, f); break;
    }
}

template <typename T>
void AVL<T>::printAVL(Traversal order) const
{
    traverse(order, [](T& value) {std::cout << value << " ";});
    std::cout << '\n';
}


#endif