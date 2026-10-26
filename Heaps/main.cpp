#include "heap.h"

int main()
{
    auto comparator = [](int a, int b)
    {
        return a > b;
    };

    Heap<int, decltype(comparator)> heap = {1, 2, 3, 4, 5};

    heap.push(8);
    heap.push(9);
    heap.pop();

    


    return 0;
}