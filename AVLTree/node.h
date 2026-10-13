#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node
{
    T data;
    Node<T> *left  = nullptr;
    Node<T> *right = nullptr;
    int height     = 0;

    Node(const T& d) : data(d) {}
};

#endif