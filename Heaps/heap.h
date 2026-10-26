#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <initializer_list>

template<typename T>
class Heap
{
private:
    std::vector<T> arr;

    static int _parent (int i) { return (i - 1) / 2; }
    static int _left   (int i) { return 2 * i + 1; }
    static int _right  (int i) { return 2 * i + 2; }
    
    void _upMaxHeap   (int i);
    void _downMaxHeap (int i);

public:
    Heap() = default;
    Heap(const std::initializer_list<T>& list);

    void push (const T& data);
    void pop  ();
    const T& top() const;        // returns largest for max heap, smallest for min heap

    int  size()  const;
    bool empty() const;

    void printLevelOrder() const;
};

#include "heap.cpp"

#endif