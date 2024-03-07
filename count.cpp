#include "copyClass/TreeCopy"
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
    Binary<int> tree1 = {1, 2, 3, 4, 2, 2};

    tree1.discard(2);

    print(tree1);

    std::cout << tree1.count(2);

}