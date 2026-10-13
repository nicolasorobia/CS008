#ifndef BSTREE_CPP
#define BSTREE_CPP

#include "bstree.h"

template<typename T>
void BSTree<T>::_push(Node<T>*& node, const T& data)
{
    // empty - add node with data
    if (node == nullptr) {
        node = new Node<T>(data);
        ++_size;
        return;
    }

    if (data < node->data)
        _push(node->left, data);
    else if (data > node->data)
        _push(node->right, data);
}

// helper node for _pop
template<typename T>
Node<T>* findPredecessor(Node<T>* node)
{
    // iterative
    // while (node->right != nullptr) {
    //     node = node->right;
    // }

    // return node;

    if (node->right == nullptr) return node;

    return findPredecessor(node->right);
}

template<typename T>
Node<T>* BSTree<T>::_remove(Node<T>*& node, const T& data)
{
    // not found - do nothing
    if (node == nullptr) return nullptr;

    if (data < node->data)
        _remove(node->left, data);
    else if (data > node->data)
        _remove(node->right, data);
    else
    {   
        // node only has a right child
        if (node->left == nullptr) {
            Node<T>* temp = node->right;
            delete node;
            node = temp;
            --_size;
            return node;
        }

        // node only has a left child
        if (node->right == nullptr) {
            Node<T>* temp = node->left;
            delete node;
            node = temp;
            --_size;
            return node;
        }

        // node has two childs
        Node<T>* temp = findPredecessor(node->left);
        node->data = temp->data;
        _remove(node->left, temp->data);
    }

    return node;
}

template<typename T>
void BSTree<T>::_clear(Node<T>* node)
{
    if (node == nullptr) return;

    _clear(node->left);
    _clear(node->right);
    delete node;
}

template<typename T>
void BSTree<T>::_preorder(Node<T>* node, void (*f)(T&))
{
    if (node == nullptr) return;

    f(node->data);
    _preorder(node->left, f);
    _preorder(node->right, f);
}

template<typename T>
void BSTree<T>::_inorder(Node<T>* node, void (*f)(T&))
{
    if (node == nullptr) return;

    _inorder(node->left, f);
    f(node->data);
    _inorder(node->right, f);
}

template<typename T>
void BSTree<T>::_postorder(Node<T>* node, void (*f)(T&))
{
    if (node == nullptr) return;

    _postorder(node->left, f);
    _postorder(node->right, f);
    f(node->data);
}

template<typename T>
Node<T>* BSTree<T>::_copy(Node<T>* node)
{
    if (node == nullptr) return nullptr;

    Node<T>* temp = new Node<T>(node->data);
    temp->left  = _copy(node->left);
    temp->right = _copy(node->right);

    return temp;
}

template<typename T>
BSTree<T>::~BSTree()
{
    _clear(root);
}

template<typename T>
BSTree<T>::BSTree(const BSTree<T>& tree)
{
    root = _copy(tree.root);
    _size = tree._size;
}

template<typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree<T>& tree)
{
    if (this == &tree) return *this;

    _clear(root);
    root = _copy(tree.root);
    _size = tree._size;

    return *this;
}

#endif