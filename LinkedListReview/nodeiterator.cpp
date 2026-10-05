#ifndef NODEITERATOR_CPP
#define NODEITERATOR_CPP

#include "nodeiterator.h"

template <typename T>
NodeIterator<T>::NodeIterator(Node<T>* current) : _current(current) {}

template <typename T>
T& NodeIterator<T>::operator*() const
{
    return _current->data;
}

template <typename T>
T& NodeIterator<T>::operator->() const
{
    return &_current->data;
}

template <typename T>
NodeIterator<T>& NodeIterator<T>::operator++()
{
    _current = _current->next; // advance, then return self
    return *this;
}

template <typename T>
NodeIterator<T> NodeIterator<T>::operator++(int)
{
    NodeIterator<T> old = *this; // save current self
    _current = _current->next;   // advance for next record
    return old;
}

template <typename T>
NodeIterator<T>& NodeIterator<T>::operator--()
{
    _current = _current->prev;
    return *this;
}

template <typename T>
NodeIterator<T> NodeIterator<T>::operator--(int)
{
    NodeIterator<T> old = *this; 
    _current = _current->prev;   
    return old;
}

#endif