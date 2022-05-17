#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include "OpenBracketsHeader.h"

using namespace std;

int main()
{
    // Устанавливаем русский язык
    setlocale(LC_ALL, "Russian"); 

    // Node - parent, fChild, sChild, value (поля структуры)
    int expectedRoot = -1;
    vector<Node> expectedTree = { {-1, 2, 3, "-"}, {1, 4, 5, "+"}, {1, NotExist, NotExist, "c"}, {2, NotExist, NotExist, "a"}, {2, NotExist, NotExist, "b"} };

    int outputRoot = -1;
    vector<Node> outputTree = { {-1, 2, 3, "-"}, {1, 4, 5, "+"}, {1, NotExist, NotExist, "c"}, {2, NotExist, NotExist, "a"}, {2, NotExist, NotExist, "b"} };

    bool isEqualTree = isEqualTrees(expectedTree, expectedRoot, outputTree, outputRoot);

    if (isEqualTree)
        cout << "Совпадение\n";
    else
        cout << "Нет совпадения\n";

    return 0;
}

// Сравнить два дерева между собой
bool isEqualTrees(vector<Node> firstTree, int rootOfFirstTree, vector<Node> secondTree, int rootOfSecondTree)
{
    bool isEqualTrees = false; // Считать, что деревья не равны между собой
    bool isEqualRoots = false; // Считать, что корни деревьев различны
    bool isEqualContent = true; // Считать, что вершины деревьев совпадают
    
    // Если корни деревьев совпадают, то считать, что они равны
    if (rootOfFirstTree == rootOfSecondTree) isEqualRoots = true;

    // Для каждой вершины первого дерева и пока предыдущщие вершины совпадают
    for (int i = 0; i < firstTree.size() && isEqualContent; i++)
    {
        // Если соответствующая вершина второго дерева не идентична, то считать что вершины вершины деревьев не совпадают
        if (!(firstTree[i] == secondTree[i])) isEqualContent = false;
    }

    // Если корни деревьев и верщины совпадают, то считать что деревья равны
    if (isEqualRoots && isEqualContent) isEqualTrees = true;

    return isEqualTrees;
}