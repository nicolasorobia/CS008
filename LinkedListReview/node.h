#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node
{
    T data;
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;
};

#endif