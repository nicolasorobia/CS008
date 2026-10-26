#ifndef HEAP_CPP
#define HEAP_CPP

#include "heap.h"
#include <utility>
#include <queue>
#include <iostream>

template <typename T>
void Heap<T>::_upMaxHeap(int i)
{
    if (i == 0) return;
    int parent = _parent(i);
    if (arr[i] > arr[parent])
    {
        std::swap(arr[i], arr[parent]);
        _upMaxHeap(parent);
    }
}

template <typename T>
void Heap<T>::_downMaxHeap(int i)
{
    int n = arr.size();
    int left  = _left(i);
    int right = _right(i);
    int largest = i;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        _downMaxHeap(largest);
    }
}

template <typename T>
Heap<T>::Heap(const std::initializer_list<T>& list)
{
    for (const T& data: list) push(data);
}

template <typename T>
void Heap<T>::push(const T& data)
{
    arr.push_back(data);
    _upMaxHeap(arr.size() - 1);
}

template <typename T>
void Heap<T>::pop()
{
    if (arr.empty()) return;

    arr[0] = arr.back(); // last value replaces the top
    arr.pop_back();
    if (!arr.empty()) _downMaxHeap(0);
}

template <typename T>
const T& Heap<T>::top() const
{
    return arr[0];
}

template <typename T>
int Heap<T>::size() const
{
    return arr.size();
}

template <typename T>
bool Heap<T>::empty() const
{
    return arr.empty();
}

template <typename T>
void Heap<T>::printLevelOrder() const
{
    int n = arr.size();
    std::queue<int> q;     
    if (n > 0) q.push(0);
    while (!q.empty()) {
        int i = q.front();
        std::cout << arr[i] << " ";
        if (_left(i) < n)  q.push(_left(i));
        if (_right(i) < n) q.push(_right(i));
        q.pop();
    }
    std::cout << '\n';
}

#endif