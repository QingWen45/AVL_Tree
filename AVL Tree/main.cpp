#include <iostream>
#include "AVLTree.h"

int main()
{
    AVLTree tree;
    int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
    for (int i : arr) {
        tree.insert(i);
        tree.print();
    }
    // tree.remove(8);
    tree.print();
    return 0;
}
