#include "heap.h"

int main()
{
    // initializer-list constructor
    Heap<int> heap{30, 10, 50, 20, 40};
    std::cout << "heap: "; heap.printLevelOrder();
    std::cout << "size: " << heap.size() << '\n';
    std::cout << "top:  " << heap.top() << '\n';

    heap.push(999);
    std::cout <<"\nAfter pushing 999, should be on top\n";
    std::cout << "heap: "; heap.printLevelOrder();
    std::cout << "top:  " << heap.top() << '\n';

    heap.pop();
    std::cout <<"\nAfter popping 999, back to original\n";
    std::cout << "heap: "; heap.printLevelOrder();
    std::cout << "top:  " << heap.top() << '\n';

    std::cout <<"\nPop everything & check if it's empty\n";
    while (!heap.empty())
    {
        std::cout << heap.top() << " and size: " << heap.size() << '\n';
        heap.pop();
    }
    std::cout << "size: " << heap.size() << '\n';
    std::cout << "Is it empty: " << std::boolalpha << heap.empty() << '\n';


    return 0;
}