#include <iostream>
#include <vector>
#include <fstream>

#include "OpenBracketsHeader.h"

using namespace std;

int main()
{
    // Устанавливаем русский язык
    setlocale(LC_ALL, "Russian"); 

    vector<Node> tree(MaxSize); // Дерево, представляющее из себя вектор из его узлов
    int root; // Идентификатор корня дерева

    // Считать и построить дерево
    bool isInputSuccess = inputTree(tree, root); 

    // Раскрыть скобки в дереве разбора выражений
    openBrackets(tree, root); 

    // Вывести результирующее дерево
    bool isOutputSuccess = outputTree(tree, root); 

    return 0;
}

//! Сравнить два дерева между собой
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

//! Заполнить входное дерево до максимального размера
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
            // Раскрыть скобки у дерева, спускаясь вниз по нему, относительно текущего узла
            openBrackets(tree, currentNode);
        }
    }

    // Если текуший узел является операцией вычитания
    if (tree[currentNode].value == "-") {
        
        // Если у внуки являются операциями вычитания или сложения
        if (tree[tree[currentNode].secondChild].value == "-" || tree[tree[currentNode].secondChild].value == "+") 
        {
            // Перестроить часть дерева относительнно текущего узла
            replaceTree(tree, currentNode, tree[currentNode].value);

            // Раскрыть скобки у дерева, спускаясь вниз по нему, относительно текущего узла
            openBrackets(tree, currentNode);
        }
    }
}

//! Перестроить часть дерева ниже текущего узла в соответствии с операцией
void replaceTree(vector<Node>& tree, int currentNode, string operation)
{
    // Если операция текущего узла вычитание
    if (operation == "-")
    {   
        // Поменять местами первого ребенка со вторым
        swap(tree[currentNode].firstChild, tree[currentNode].secondChild);

        // Поменять второго ребенка и внука первого ребенка местами
        swap(tree[currentNode].secondChild, tree[tree[currentNode].firstChild].firstChild);

        // Привязать родителей
        tree[tree[currentNode].secondChild].parent = currentNode;
        tree[tree[tree[currentNode].firstChild].firstChild].parent = tree[currentNode].firstChild;

        // Если операция у внука сложение
        if (tree[tree[currentNode].firstChild].value == "+") 
        {
            // Поменять её на вычитание
            tree[tree[currentNode].firstChild].value = "-";
        }
        else if (tree[tree[currentNode].firstChild].value == "-") // Иначе если операция вычитание
        {
            // Поменять её на сложение
            tree[tree[currentNode].firstChild].value = "+";
        }
    }
    else
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
                greatgrandchildren[2] = copyVertex(tree, grandchildren[0]);
                greatgrandchildren[3] = grandchildren[3];
                greatgrandchildren[4] = grandchildren[1];
                greatgrandchildren[5] = copyVertex(tree, grandchildren[2]);
                greatgrandchildren[6] = copyVertex(tree, grandchildren[1]);
                greatgrandchildren[7] = copyVertex(tree, grandchildren[3]);
            }
            //Иначе если второй ребёнок является сложением
            else if (tree[secondChild].value == "+")
            {
                // Перестраиваем дерево в соответствии с этим случаем
                greatgrandchildren[0] = grandchildren[0];
                greatgrandchildren[1] = grandchildren[2];
                greatgrandchildren[2] = grandchildren[1];
                greatgrandchildren[3] = copyVertex(tree, grandchildren[2]);
                greatgrandchildren[4] = copyVertex(tree, grandchildren[0]);
                greatgrandchildren[5] = grandchildren[3];
                greatgrandchildren[6] = copyVertex(tree, grandchildren[1]);
                greatgrandchildren[7] = copyVertex(tree, grandchildren[3]);
            }
            // Иначе
            else
            {
                // Перестраиваем дерево для всех остальных случаев
                greatgrandchildren[0] = grandchildren[0];
                greatgrandchildren[1] = grandchildren[2];
                greatgrandchildren[2] = copyVertex(tree, grandchildren[0]);
                greatgrandchildren[3] = grandchildren[3];
                greatgrandchildren[4] = grandchildren[1];
                greatgrandchildren[5] = copyVertex(tree, grandchildren[3]);
                greatgrandchildren[6] = copyVertex(tree, grandchildren[1]);
                greatgrandchildren[7] = copyVertex(tree, grandchildren[2]);
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
                tree[greatgrandchildren[i * 2]].parent = tree.size() - 1;
                tree[greatgrandchildren[i * 2 + 1]].parent = tree.size() - 1;
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
            int grandchildren[4] = { tree[firstChild].firstChild, tree[currentNode].secondChild, tree[firstChild].secondChild, copyVertex(tree, tree[currentNode].secondChild) };

            //был - => -; был + стал +
            tree[currentNode].value = tree[firstChild].value;
            tree[firstChild].value = "";

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

                tree[grandchildren[i * 2]].parent = tree.size() - 1;
                tree[grandchildren[i * 2 + 1]].parent = tree.size() - 1;
            }

            // Привязываем внуков к родителям в правильном порядке
            tree[currentNode].firstChild = tree.size() - 2;
            tree[currentNode].secondChild = tree.size() - 1;
        }
        return;
    }
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

    return true;
}

//! Вывести дерево разбора выражений
bool outputTree(vector<Node>& tree, int& current)
{
    cout << "\n";
    int tree_size = 0;
    for (int i = 0; i < tree.size(); ++i)
    {
        if (tree[i].value != "")
            tree_size++;
    }
    cout << tree_size;

    dfsOutput(tree, current);

    return true;
}

//! Вывести сообщение об ошибке
bool crashOutput(ErrorType error)
{
    bool isSuccessOutput = false;

    switch (error)
    {
        case NO_ERROR:
            isSuccessOutput = false;
            break;

        case INPUT_FILE_NOT_EXIST:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case UNKNOWN_FILE_EXTENSION:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case OUTPUT_FILE_CREATION_FAILED:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case WRONG_DATA_FORMAT:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case NOT_BINARY_TREE:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case SAME_NODES_ID:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case SAME_PARENT_AND_NODE_ID:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case LACK_OF_OPERANDS:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case NODE_ID_OUT_OF_RANGE:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case PARENT_ID_OUT_OF_RANGE:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case INVALID_NODE_SYMBOL:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case UNSUPPORTED_OPERATION:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case UNEXCEPTABLE_PARENT_ID:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case NO_ROOT:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case TREE_SIZE_OUT_OF_RANGE:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;

        case INVALID_NUMBER_OF_NODES:
            cout << "bla bla bla";
            isSuccessOutput = true;
            break;
        default:
            cout << "Произошла неизвестная ошибка. Попробуйте перезапустить программу." << endl;
            isSuccessOutput = true;
            break;
    }

    return isSuccessOutput;
}

//! Проверить дерево на ошибки
ErrorType checkOnErrors(int& size, vector<Node>& tree, int& root)
{
    if (root != NotExist)
    {
        return NO_ROOT;
    }
    else
    {
        return NO_ERROR;
    }
}

//! Вывести вершины дерева обходом в глубину
void dfsOutput(vector<Node>& tree, int current)
{
    cout << "\n" << current << " " << tree[current].parent << " " << tree[current].value;
    if (tree[current].firstChild != NotExist)
        dfsOutput(tree, tree[current].firstChild);
    if (tree[current].secondChild != NotExist)
        dfsOutput(tree, tree[current].secondChild);
}

//! Скопировать заданную вершину в векторе вершин
int copyVertex(vector<Node>& tree, int currentNode)
{
    int pos; // Позиция для вставки

    // Если идентификатор копируемой вершины в пределах размера вектора
    if (currentNode < tree.size() || currentNode >= 1)
    {
        // Считать, что позиция для вставки запоследний элемент вектора
        pos = tree.size();

        // Добавить в конец вектора копируемую вершину
        tree.push_back(tree[currentNode]);

        // Если у копируемой вершины не отсутствует первый ребёнок
        if (tree[currentNode].firstChild != NotExist) {
            // Считать первым ребенком текущей вершины его копию
            tree[currentNode].firstChild = copyVertex(tree, tree[currentNode].firstChild);
        }

        // Если у копируемой вершины не отсутствует второй ребёнок
        if (tree[currentNode].secondChild != NotExist) {
            // Считать вторым ребенком текущей вершины его копию
            tree[currentNode].secondChild = copyVertex(tree, tree[currentNode].secondChild);
        }
    }
    else
    {
        // Считать, что позиции для вставки не существует
        pos = -1;
    }

    return pos;
}