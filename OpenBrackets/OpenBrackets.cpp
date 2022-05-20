#include <iostream>
#include <vector>
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

    // Если размеры деревьев не совпадают, считать что их вершины не совпадают
    if (firstTree.size() != secondTree.size()) isEqualContent = false;

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

// Заполнить входное дерево до максимального размера
void initializeFullTree(vector<Node>& inputTree)
{
    for (int i = inputTree.size() - 1; i < MaxSize - 1; i++)
    {
        inputTree.push_back(Node());
    }
}

//! Раскрыть скобки в заданном выражении
void openBrackets(vector<Node>&tree, int currentNode)
{

    // Если у текущего узла дерева существует первый ребёнок
    if (tree[currentNode].firstChild != NotExist)
    {
        openBrackets(tree, tree[currentNode].firstChild); // Раскрыть скобки у дерева, спускаясь вниз по нему, относительно первого ребёнка
    }
    
    // Если у текущего узла дерева существует второй ребёнок
    if (tree[currentNode].secondChild != NotExist) 
    {
        openBrackets(tree, tree[currentNode].secondChild); // Раскрыть скобки у дерева, спускаясь вниз по нему, относительно второго ребёнка
    }
    
     // Если текущий узел является операцией умножения или побитового умножения
    if (tree[currentNode].value == "*" || tree[currentNode].value == "&")
    {
        // Перестроить часть дерева относящуюся к текущему узлу
        replaceTree(tree, currentNode, tree[currentNode].value);

        // Если после перестройки куска дерева текущий узел не является операцией умножения или побитового умножения
        if (tree[currentNode].value != "*" && tree[currentNode].value != "&")
        {
            //  Раскрыть скобки у дерева, спускаясь вниз по нему, относительно текущего узла
            openBrackets(tree, currentNode);
        }
    }
}

//! Перестроить часть дерева ниже текущего узла в соответствии с операцией
void replaceTree(vector<Node>& tree, int currentNode, string operation)
{
    
        // Получить первого ребёнка текущего узла (с операцией высшего приоритета)
        int firstChild = tree[currentNode].firstChild;
        // Получить второго ребёнка текущего узла (с операцией высшего приоритета)
        int secondChild = tree[currentNode].secondChild;
        // Если первый ребёнок является операцией с низшим приоритетом и второй ребёнок является операцией с низшим приоритетом
        if ((tree[firstChild].value == "+" || tree[firstChild].value == "-") && (tree[secondChild].value == "+" || tree[secondChild].value == "-"))
        {
        // Создаём внуков и правнуков для текущего узла
        int grandchildren[4] = { tree[firstChild].firstChild, tree[firstChild].secondChild, tree[secondChild].firstChild, tree[secondChild].secondChild };
        int greatgrandchildren[8];
        

        // Если первый ребёнок текущего узла является сложением
        if (tree[firstChild].value == "+")
        {
	        // Перестраиваем дерево в соответствии с этим случаем
            greatgrandchildren[0] = grandchildren[0];
            greatgrandchildren[1] = grandchildren[2];
            greatgrandchildren[2] = grandchildren[0];
            greatgrandchildren[3] = grandchildren[3];
            greatgrandchildren[4] = grandchildren[1];
            greatgrandchildren[5] = grandchildren[2];
            greatgrandchildren[6] = grandchildren[1];
            greatgrandchildren[7] = grandchildren[3];
        }
        //Иначе если второй ребёнок является сложением
        else if (tree[secondChild].value == "+")
        {
	        // Перестраиваем дерево в соответствии с этим случаем
            greatgrandchildren[0] = grandchildren[0];
            greatgrandchildren[1] = grandchildren[2];
            greatgrandchildren[2] = grandchildren[1];
            greatgrandchildren[3] = grandchildren[2];
            greatgrandchildren[4] = grandchildren[0];
            greatgrandchildren[5] = grandchildren[3];
            greatgrandchildren[6] = grandchildren[1];
            greatgrandchildren[7] = grandchildren[3];
        }
        // Иначе
        else
        {
	        // Перестраиваем дерево для всех остальных случаев
            greatgrandchildren[0] = grandchildren[0];
            greatgrandchildren[1] = grandchildren[2];
            greatgrandchildren[2] = grandchildren[0];
            greatgrandchildren[3] = grandchildren[3];
            greatgrandchildren[4] = grandchildren[1];
            greatgrandchildren[5] = grandchildren[3];
            greatgrandchildren[6] = grandchildren[1];
            greatgrandchildren[7] = grandchildren[2];
        }
        // Присваиваем текущему узлу операцию сложения тк первое значение всегда прибавляется
        tree[currentNode].value = '+';

        // Если первый или второй ребёнок является операцией вычитания
        if (tree[firstChild].value == "-" || tree[secondChild].value == "-")
        {
	        // Присвоить и первому и второму ребёнку операцию вычитания
            tree[firstChild].value = "-";
            tree[secondChild].value = "-";
        }

        Node summands[4]; // либо * &

        // Для каждого из 4 внуков (слагаемых)
        for (int i = 0; i < 4; ++i)
        {
            summands[i].value = operation;
	        // Подключить первую пару слагаемых к первому ребёнку
            if (i < 2) 
            {
                summands[i].parent = firstChild;
            }
            // Подключить вторую пару слагаемых ко второму ребёнку
            else
            {
                summands[i].parent = secondChild;
            }
            
            // Подключить правнуков ко внукам
            summands[i].firstChild = greatgrandchildren[i * 2];
            summands[i].secondChild = greatgrandchildren[i * 2 + 1];
            // Добавить внука в дерево
            tree.push_back(summands[i]);
        }

        // Привязываем внуков к родителям в правильном порядке
        tree[firstChild].firstChild = tree.size() - 4;
        tree[firstChild].secondChild = tree.size() - 3;
        tree[secondChild].firstChild = tree.size() - 2;
        tree[secondChild].secondChild = tree.size() - 1;

        // Досрочно завершить функцию
        return;
        }

        // ситуация попроще (один +)
        // смена мест для сведение к нижнему if
        if (tree[secondChild].value == "+" || tree[secondChild].value == "-")
        {
            swap(secondChild, firstChild);
            swap(tree[currentNode].firstChild, tree[currentNode].secondChild);
        }

        // Если только один из детей текущего узла является операцией с низшим приоритетом
        if (tree[firstChild].value == "+" || tree[firstChild].value == "-")
        {
	        // Запоминаем внуков узла
            int grandchildren[4] = { tree[firstChild].firstChild, tree[currentNode].secondChild, tree[firstChild].secondChild, tree[currentNode].secondChild };

            //был - => -; был + стал +
            tree[currentNode].value = tree[firstChild].value;
            Node summands[2];

	        // Для каждого из двух внуков (слагаемых)
            for (int i = 0; i < 2; ++i)
            {
	            // Присвоить текущую операцию слагаемому и привязать его к текущему узлу
                summands[i].value = operation;
                summands[i].parent = currentNode;

	            // Подключить внуков к слагаемым
                summands[i].firstChild = grandchildren[i * 2];
                summands[i].secondChild = grandchildren[i * 2 + 1];
	            // Добавить слагаемое в дерево
                tree.push_back(summands[i]);
            }

        // Привязываем внуков к родителям в правильном порядке
        tree[currentNode].firstChild = tree.size() - 2;
        tree[currentNode].secondChild = tree.size() - 1;
        }
    return;
}

//! Ввести заданное дерево разбора выражений
bool inputTree(vector<Node>& tree, int& root)
{
    int size;
    cin >> size;

    for (int i = 0; i < size; ++i) {
        Node currentNode;
        int id;
        cin >> id;
        cin >> currentNode.parent;
        cin >> currentNode.value;
        tree[id] = currentNode;

        if (currentNode.parent == NotExist)
        {
            root = id;
        }
        else
        {
            if (tree[currentNode.parent].firstChild == NotExist)
                tree[currentNode.parent].firstChild = id;
            else
                tree[currentNode.parent].secondChild = id;
        }
    }
}

