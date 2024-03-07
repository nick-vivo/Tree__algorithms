#include "stl/libs/Tree"
#include <iostream>
#include <vector>

using namespace Tree;

template<class T>
Binary<T> repeatValuesInVector(const std::vector<T>& vec)
{
    Binary<T> tree1;
    Binary<T> tree2;
    
    for(T i : vec)
    {
        if(tree1.in(i))
            tree2.add(i);
        else
            tree1.add(i);
    }

    return tree2;
    
}

template<class T>
Binary<T> notRepeatValuesInVector(const std::vector<T>& vec)
{
    Binary<T> tree1;

    for(T i : vec)  
    {
        if(tree1.in(i))
            tree1.discard(i);
        else
            tree1.add(i);
    }

    return tree1;
    
}

int main()
{
    Binary<int> tree1 = {1, 2, 3, 4};

    Binary<int> tree2 = {3, 4, 5, 6};

    Binary<int> tree3 = intersection(tree1, tree2);

    std::cout << "\n\nIntersection: " << "\n";
    printTree(tree3);

    tree3 = (tree1 + tree2) - tree3;

    std::cout << "\n\nSummectrical: " << "\n";
    printTree(tree3);

    tree3 = (tree1 + tree2);
    std::cout << "\n\nUnion: " << "\n";
    printTree(tree3);

    std::vector<int> numbers = {1, 2, 3, 2, 4, 5, 3, 6, 4};
    std::cout << "\n\nDublicate: " << "\n";
    tree3 = repeatValuesInVector(numbers);
    printTree(tree3);

    std::cout << "\n\nnotDublicate: " << "\n";
    tree3 = notRepeatValuesInVector(numbers);
    printTree(tree3);

}