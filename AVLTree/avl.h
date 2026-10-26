#ifndef AVL_H
#define AVL_H

#include "node.h"

template<typename T>
class AVL
{
private:
    Node<T> *root = nullptr;

    int _height        (Node<T> *node) const;      // -1 for nullptr (a leaf is 0)
    int _getBF         (Node<T> *node) const;      // height(left) - height(right)
    void _updateHeight (Node<T> *node);            // 1 + taller child's height

    void _rotateLeft  (Node<T> *&node);
    void _rotateRight (Node<T> *&node);
    void _rebalance   (Node<T> *&node);

    void _push   (Node<T> *&node, const T& data);

    void _remove (Node<T> *&node, const T& data);
    Node<T>* findPredecessor(Node<T> *node);

    void _clear    (Node<T> *node);
    Node<T>* _copy (Node<T> *node) const;

    void _preorder  (Node<T> *node, void (*f)(T&)) const;
    void _inorder   (Node<T> *node, void (*f)(T&)) const;
    void _postorder (Node<T> *node, void (*f)(T&)) const;

public:
    enum class Traversal { Preorder, Inorder, Postorder};
    
    AVL() = default;

    void push (const T& value)  { _push(root, value); }
    void remove(const T& value) { _remove(root, value); }
    void clear()                { _clear(root); root = nullptr; }
    int height() const          { return _height(root); }

    void traverse(Traversal order, void (*f)(T&)) const;
    void printAVL(Traversal order) const;

    // Big 3
    ~AVL() { _clear(root); }

    AVL(const AVL<T>& tree)
    {
        root = _copy(tree.root);
    }

    AVL<T>& operator=(const AVL<T>& tree)
    {
        if (this == &tree) return *this;

        _clear(root);
        root = _copy(tree.root);

        return *this;
    }
};

#include "avl.cpp"

#endif