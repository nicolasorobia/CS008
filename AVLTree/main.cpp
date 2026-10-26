#include "avl.h"
#include <iostream>

void printAllOrders(const AVL<int>& tree)
{
    std::cout << "preorder: ";
    tree.printAVL(AVL<int>::Traversal::Preorder);
    std::cout << "inorder: ";
    tree.printAVL(AVL<int>::Traversal::Inorder);
    std::cout << "postorder: ";
    tree.printAVL(AVL<int>::Traversal::Postorder);
}

void doubleTheNodes(int& x) { std::cout << x * 2 << " "; }

int main()
{
    AVL<int> tree;
    for (int v: {10, 20, 30, 40, 50, 25}) tree.push(v);
    printAllOrders(tree);

    std::cout << "\nPass lambda function (double each node) to traversal:\n";
    std::cout << "preorder: ";
    tree.traverse(AVL<int>::Traversal::Preorder, doubleTheNodes);  std::cout << '\n';
    std::cout << "inorder: ";
    tree.traverse(AVL<int>::Traversal::Inorder, doubleTheNodes);   std::cout << '\n';
    std::cout << "postorder: ";
    tree.traverse(AVL<int>::Traversal::Postorder, doubleTheNodes); std::cout << '\n';

    tree.remove(30);
    std::cout << "\nAfter removing 30:\n";
    printAllOrders(tree);

    AVL<int> copy = tree;
    copy.push(15);
    std::cout << "\nCopy:\n";
    printAllOrders(copy);
    std::cout << "\nOriginal:\n";
    printAllOrders(tree);

    return 0;
}