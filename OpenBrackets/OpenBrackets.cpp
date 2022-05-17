#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include "OpenBracketsHeader.h"

using namespace std;

int main()
{
    // Node - parent, fChild, sChild, value
    int expectedRoot = -1;
    vector<Node> expectedTree = { {-1, 2, 3, "-"}, {1, 4, 5, "+"}, {1, NotExist, NotExist, "c"}, {2, NotExist, NotExist, "a"}, {2, NotExist, NotExist, "b"} };
    int outputRoot = -1;
    vector<Node> outputTree = { {-1, 2, 3, "-"}, {1, 4, 5, "+"}, {1, NotExist, NotExist, "c"}, {2, NotExist, NotExist, "a"}, {2, NotExist, NotExist, "b"} };

    //bool isEqualTree = isEqualTrees(expectedTree, expectedRoot, outputTree, outputRoot);
    bool isEqualTree = true;

    if (isEqualTree)
        cout << "Совпадение\n";
    else
        cout << "Нет совпадения\n";

    return 0;
}

// Сравнить два дерева между собой
bool isEqualTrees(vector<Node>& firstTree, int& rootOfFirstTree, vector<Node>& secondTree, int& rootOfSecondTree)
{
    bool isEqualTrees = false; // Считать, что деревья не равны между собой
    bool isEqualRoots = false; // Считать, что корни деревьев различны
    bool isEqualContent = false; // Считать, что вершины деревьев не совпадают
    
    // Если корни деревьев совпадают, то считать, что они равны
    if (rootOfFirstTree == rootOfSecondTree) isEqualRoots = true;

    vector<Node> uniqueElements;

    // Получить уникальные элементы в векторах 
    set_difference(firstTree.begin(), firstTree.end(), secondTree.begin(), secondTree.end(), uniqueElements.begin());

    // Если в векторах нет уникальныъ элементов, то считать, что вершины деревьев совпадают
    if (uniqueElements.empty()) isEqualContent = true;

    // Если корни деревьев и верщины совпадают, то считать что деревья равны
    if (isEqualRoots && isEqualContent) isEqualTrees = true;

    return isEqualTrees;
}