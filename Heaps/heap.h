# pragma once

#include <vector>
#include <initializer_list>

template<typename Data, typename Comparator>
class Heap
{
private:
    std::vector<Data> _data;
    Comparator _compare;
    static int getParentIndex           (int childIndex)  const;
    static int getRightChildIndex       (int parentIndex) const;
    static int getLeftChildIndex        (int parentIndex) const;
    int        getFavoriteChildIndex    (int parentIndex) const;
    void       reheapifyUp              (int childIndex);
    void       reheapifyDown            (int parentIndex);


public:
    Heap(const std::initializer_list<Data>& list);
    Heap() = default;

    void push (const Data& data);
    void pop  ();
    const Data& top() const;
    int size() const;
    bool  empty() const;


};