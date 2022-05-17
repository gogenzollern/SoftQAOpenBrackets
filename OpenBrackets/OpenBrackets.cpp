#include <iostream>
#include <vector>
#include <fstream>

#include "OpenBracketsHeader.h"

using namespace std;

int main()
{
    std::cout << "Hello World!\n"; //TODO my code
}

// Сравнить два дерева между собой
bool isEqualTrees(const vector<Node>& firstTree, const int& rootOfFirstTree, const vector<Node>& secondTree, const int& rootOfSecondTree)
{
    bool isEqualTrees = false; // Считать, что деревья не равны между собой
    bool isEqualRoots = false; // Считать, что корни деревьев различны
    bool isEqualContent = true; // Считать, что вершины деревьев совпадают
    
    // Если корни деревьев совпадают, то считать, что они равны
    // Для каждой вершины первого дерева и пока предыдущие вершины совпадают
    // Если соответствующая вершина второго дерева не идентична
    // Считать, что вершины деревьев не совпадают

    // Если корни деревьев и верщины совпадают, то считать что деревья равны
    if (isEqualRoots && isEqualContent) isEqualTrees = true;

    return isEqualTrees;
}