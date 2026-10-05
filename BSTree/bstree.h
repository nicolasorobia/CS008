#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"

template<typename T>
class BSTree {
private:
    Node<T> *root = nullptr;
    int _size = 0;

    void     _push    (Node<T>*& node, const T& data);
    Node<T>* _pop     (Node<T>*  node, const T& data);
    void     _clear   (Node<T>*  node);

    void _preorder    (Node<T> *node, void(*f)(T&));
    void _inorder     (Node<T> *node, void(*f)(T&));
    void _postorder   (Node<T> *node, void(*f)(T&));

    Node<T>* _copy    (Node<T>* node);

public:
    BSTree() = default;

    void push(const T& value) { _push(root, value); }
    void pop (const T& value) { root = _pop(root, value); }
    void clear() {
        _clear(root);
        root = nullptr;
        _size = 0;
    }

    // traversal methods
    void preorder  (void (*f)(T&)) { _preorder  (root, f); }
    void inorder   (void (*f)(T&)) { _inorder   (root, f); }
    void postorder (void (*f)(T&)) { _postorder (root, f); }

    // Big 3
    ~BSTree();
    BSTree(const BSTree<T>& tree);
    BSTree<T>& operator=(const BSTree<T>& tree);

};

#include "bstree.cpp"

#endif