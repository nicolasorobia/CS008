#include "heap.h"
#include <algorithm>
#include <iostream>

template<typename Data, typename Comparator>
void Heap<Data, Comparator>::push(const Data &data)
{
    // add data to vector
    _data.push_back(data);

    // reheapify up
    reheapifyUp(_data.size() - 1);
}

template<typename Data, typename Comparator>
void Heap<Data, Comparator>::pop()
{
    if (empty()) return;

    _data[0] = _data[_data.size() - 1];
    _data.pop_back();

    // reheapify down
    reheapifydown(0);
}

template<typename Data, typename Comparator>
void Heap<Data, Comparator>::reheapifyDown(int parentIndex)
{
    int childIndex = getLeftChildIndex(parentIndex);
    if (_compare(_data[parentIndex], _data[childIndex]))
    {
        std::cout << "WAZZZUPPPPP!\n";
    }
}