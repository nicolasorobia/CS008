#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP

#include "linkedlist.h"

// private member functions
template <typename T>
Node<T>* LinkedList<T>::createNode(const T& data)
{
    return new Node<T> {data};
}

template <typename T>
void LinkedList<T>::addFirstNode(const T& data)
{
    Node<T>* node =createNode(data);
    _head = node;
    _tail = node;
    _size = 1;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

// default constructor
template <typename T>
LinkedList<T>::LinkedList() = default;

// initializer-list constructor
template <typename T>
LinkedList<T>::LinkedList(const std::initializer_list<T>& list)
{
    for (const T& value: list) push_back(value);
}

// destructor
template <typename T>
LinkedList<T>::~LinkedList()
{
    Node<T>* current = _head;
    while (current != nullptr)
    {
        Node<T>* n = current->next;
        delete current;
        current = n;
    }
}

// copy constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
    for (Node<T> * current = other._head; current != nullptr; current = current->next)
        push_back(current->data);
}

// copy assignment (destructor + copy)
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
    if (this == &other) return *this; // self assignment, do nothing

    // free our current nodes (destructor)
    Node<T>* current = _head;
    while (current != nullptr)
    {
        Node<T>* n = current->next;
        delete current;
        current = n;
    }
    _head = _tail = nullptr;
    _size = 0;

    // deep-copy (copy constructor)
    for (Node<T>* n = other._head; n != nullptr; n = n->next)
        push_back(n->data);

    return *this;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

// public member functions

// insert an item at the end of the list
template <typename T>
void LinkedList<T>::push_back(const T& data)
{
    // if list is empty, add its first ever node with the data passed by user
    if (_head == nullptr)
    {
        addFirstNode(data);
        return;
    }

    Node<T>* node = createNode(data);
    node->prev = _tail;
    _tail->next = node;
    _tail = node;
    ++_size;
}

// insert an item at the beginning of the list
template <typename T>
void LinkedList<T>::push_front(const T& data)
{
    if (_head == nullptr)
    {
        addFirstNode(data);
        return;
    }

    Node<T>* node = createNode(data);
    node->next = _head;
    _head->prev = node;
    _head = node;
    ++_size;
}

// remove tail from list
template <typename T>
void LinkedList<T>::pop_back()
{
    // empty list
    if (_head == nullptr) return;

    // only a single node
    if (_head == _tail)
    {
        delete _tail;
        _head = _tail = nullptr;
        _size = 0;
        return;
    }

    Node<T>* toDelete = _tail;
    _tail = _tail->prev;
    _tail->next = nullptr;
    delete toDelete;
    --_size;
}

// remove head from list
template <typename T>
void LinkedList<T>::pop_front()
{
    if (_head == nullptr) return;

    if (_head == _tail)
    {
        delete _head;
        _head = _tail = nullptr;
        _size = 0;
        return;
    }

    Node<T>* toDelete = _head;
    _head = _head->next;
    _head->prev = nullptr;
    delete toDelete;
    --_size;
}

// clear the lsit
template <typename T>
void LinkedList<T>::clear()
{
    Node<T>* current = _head;
    while (current != nullptr)
    {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    _head = _tail = nullptr;
    _size = 0;
}

// find an item
template <typename T>
Node<T>* LinkedList<T>::findNode(const T& target) const
{
    Node<T> * current = _head;
    while (current != nullptr && current->data != target)
        current = current->next;

    return current;
}

// insert before a particular node
template <typename T>
void LinkedList<T>::insertBefore(const T& target, const T& data)
{
    // find the node holding target
    Node<T> * current = findNode(target);

    if (current == nullptr) return; // target not found
    if (current == _head) { push_front(data); return; } // if target is head, insert before head

    Node<T>* node = createNode(data);
    Node<T>* before = current->prev;

    node->prev = before;
    node->next = current;
    before->next = node;
    current->prev = node;
    ++_size;
}

// insert after a particular node
template<typename T>
void LinkedList<T>::insertAfter(const T& target, const T& data)
{
    Node<T> * current = findNode(target);

    if (current == nullptr) return; // target not found
    if (current == _tail) { push_back(data); return; } // if target is tail, insert after tail

    Node<T>* node = createNode(data);
    Node<T>* after = current->next;

    node->prev = current;
    node->next = after;
    current->next = node;
    after->prev = node;
    ++_size;
}

// get data from beginning of the list
template <typename T>
const T& LinkedList<T>::front() const { return _head->data; }

// get data from end of the list
template <typename T>
const T& LinkedList<T>::back() const { return _tail->data; }

// check size of the list
template <typename T>
int LinkedList<T>::size() const { return _size; }

// check if list is empty
template <typename T>
bool LinkedList<T>::empty() const { return _size == 0; }

// print all the items in the list
template <typename U>
std::ostream& operator<<(std::ostream& out, const LinkedList<U>& list)
{
    out << "[";
    for (Node<U>* current = list._head; current != nullptr; current = current->next)
    {
        out << current->data;
        if (current->next != nullptr) out << ", ";
    }
    out << "]";

    return out;
}

#endif
