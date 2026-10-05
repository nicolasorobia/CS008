#include "bstree.h"
#include <iostream>

int main()
{
    int values[] {29, 20, 1, 0, 8, 6, 3, 26, 38, 100};
    BSTree<int> tree;
    for (int v: values) {
        tree.push(v);
    }

    auto print = [](int& x) { std::cout << x << " "; };

    std::cout << "preorder:  "; tree.preorder(print); std::cout <<"\n";
    std::cout << "inorder:   "; tree.inorder(print); std::cout <<"\n";
    std::cout << "postorder: "; tree.postorder(print); std::cout <<"\n";

    std::cout << "\n-- Test copy functionalities --\n";

    BSTree<int> copy = tree;
    copy.push(777);
    tree.pop(100);

    std::cout << "original: "; tree.inorder(print); std::cout << "\n";
    std::cout << "copy:     "; copy.inorder(print); std::cout << "\n";

    tree.clear();
    std::cout << "original (after clear): "; tree.inorder(print); std::cout << "\n";

    tree = copy;
    std::cout << "original (after assign): "; copy.inorder(print); std::cout << "\n";

    return 0;
}