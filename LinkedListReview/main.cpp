#include "linkedlist.h"
#include "nodeiterator.h"
#include <iostream>
#include <algorithm>

int main()
{
    LinkedList<int> a {24, 34, 3, 124, 65, 90};

    auto ans = std::minmax_element(a.begin(), a.end());

    std::cout << "min element of a: " << *ans.first  << "\n"; // 3
    std::cout << "max element of a: " << *ans.second << "\n"; // 124

    return 0;
}