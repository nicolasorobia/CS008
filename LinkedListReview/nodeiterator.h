#ifndef NODEITERATOR_H
#define NODEITERATOR_H

#include "Node.h"
#include <iterator>

/*
    NOTE: ONLY COMPATIBLE WITH C++11, declare traits manually in public as per modern C++ standards (17, 20, 23)
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using reference         = T&;
*/

template <typename T>
class NodeIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
private:
    Node<T>* _current;              // this is our walker

public:
    NodeIterator(Node<T>* current = nullptr);

    T& operator*()  const;          // dereference -> element
    T& operator->() const;          // member access

    NodeIterator& operator++();     // prefix  ++it
    NodeIterator  operator++(int);  // postfix it++

    NodeIterator& operator--();    
    NodeIterator  operator--(int);

    template <typename U>
    friend bool operator==(const NodeIterator<U>& a, const NodeIterator<U>& b)
    {
        return a._current == b._current;
    }

    template <typename U>
    friend bool operator!=(const NodeIterator<U>& a, const NodeIterator<U>& b)
    {
        return !(a == b);
    } 
};

#include "nodeiterator.cpp"

#endif