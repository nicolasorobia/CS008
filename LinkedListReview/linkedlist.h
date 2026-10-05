#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"
#include "nodeiterator.h"
#include <initializer_list>
#include <ostream>

template <typename T>
class LinkedList
{
private:
    Node<T> *_head = nullptr;
    Node<T> *_tail = nullptr;
    int      _size {0};

    Node<T>* createNode(const T& data);                  // returns a dynamically created node containing data
    void addFirstNode(const T& data);                    // add the first node to the list

public:
    LinkedList();                                        // default
    LinkedList(const std::initializer_list<T>& list);    // initializer-list constructor
    
    // Big 3
    ~LinkedList();                                       // destructor
    LinkedList(const LinkedList<T>& list);               // copy
    LinkedList<T>& operator=(const LinkedList<T>& list); // operator

    void push_back(const T& data);                       // push data to the tail side of the list
    void push_front(const T& data);                      // push data to the head side of the list
    void pop_back();                                     // remove tail from list
    void pop_front();                                    // remove head from list
    void clear();                                        // clear the list

    Node<T>* findNode(const T& target) const;            // find an item
    void insertBefore(const T& target, const T& data);   // add data before the first instance of target
    void insertAfter(const T& target, const T& data);    // add data after the first instance of target
                   
    const T& front() const;                              // get data from beginning of the list
    const T& back() const;                               // get data from end of the list
    int size() const;                                    // return the size of the linked list
    bool empty() const;                                  // return true if list is empty, else false
    
    // prints entire list
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, const LinkedList<U>& list);

    NodeIterator<T> begin() { return NodeIterator<T>(_head);   }
    NodeIterator<T> end()   { return NodeIterator<T>(nullptr); }

};

#include "linkedlist.cpp"

#endif