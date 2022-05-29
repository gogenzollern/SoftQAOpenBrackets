/*!
* \file Файл исходного кода программы
* Файл содержит в себе реализацию функций программы
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <fstream>

#include "OpenBracketsHeader.h"

using namespace std;

int main(int argc, char* argv[])
{
    // Устанавливаем русский язык
    setlocale(LC_ALL, "Russian"); 

    ifstream fin; // Поток ввода
    ofstream fout; // Поток вывода
    vector<Node> tree(MaxSize); // Дерево, представляющее из себя вектор из его узлов
    int root; // Идентификатор корня дерева

    // Считать и построить дерево
    bool isInputSuccess = inputTree(argc, argv, fin, tree, root);

    if (isInputSuccess)
    {
        // Раскрыть скобки в дереве разбора выражений
        openBrackets(tree, root);
        // Вывести результирующее дерево
        bool isOutputSuccess = outputTree(argc, argv, fout, tree, root);
    }

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

// Раскрыть скобки в заданном выражении
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

// Перестроить часть дерева ниже текущего узла в соответствии с операцией
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

// Ввести заданное дерево разбора выражений
bool inputTree(int argc, char* argv[], ifstream& fin, vector<Node>& tree, int& root)
{
    bool isCrashed = false;
    int size;

    // Если количество файлов в командной строке не равно 3
    if (argc != 3) {
        cerr << "Аргументы командной строки заданы неверно" << endl;
        return false;
    }

    // Запоминаем имена входного и выходного файлов
    string file1 = argv[1];

    // Если расширение входного файла не равно txt
    if (file1.substr(file1.rfind('.') + 1, string::npos) != "txt") {
        isCrashed = crashOutput(UNKNOWN_FILE_EXTENSION);
        return false;
    }

    fin.open(file1);

    // Если не удалось открыть
    if (!fin.is_open()) {
        isCrashed = crashOutput(INPUT_FILE_NOT_EXIST);
        return false;
    }
    else
    {
        try
        {
            if (!(fin >> size))
                throw (WRONG_DATA_FORMAT);

            if (size > MaxSize || size < 1)
                throw (TREE_SIZE_OUT_OF_RANGE);
        }
        catch (exception& e)
        {
            isCrashed = crashOutput(WRONG_DATA_FORMAT);
            return false;
        }
        catch (ErrorType er)
        {
            isCrashed = crashOutput(er);
            return false;
        }

        for (int i = 0; i < size; ++i) {
            Node currentNode;
            int id;

            try
            {
                if (!(fin >> id))
                    throw(WRONG_DATA_FORMAT);

                if (!(fin >> currentNode.parent))
                    throw(WRONG_DATA_FORMAT);

                if (!(fin >> currentNode.value))
                    throw(WRONG_DATA_FORMAT);

                if (id > MaxSize || id < 1)
                    throw (NODE_ID_OUT_OF_RANGE);

                if ((currentNode.parent > MaxSize || currentNode.parent < 1) && (currentNode.parent != NotExist))
                    throw (PARENT_ID_OUT_OF_RANGE);
            }
            catch (exception& e)
            {
                isCrashed = crashOutput(WRONG_DATA_FORMAT);
                return false;
            }
            catch (ErrorType er)
            {
                isCrashed = crashOutput(er);
                return false;
            }

            if (id >= MaxSize || (id < 1))
            {
                isCrashed = crashOutput(NODE_ID_OUT_OF_RANGE);
                return false;
            }

            // Если узел с указанным id еще не существует
            if (tree[id].value == "" && tree[id].parent == NotExist && tree[id].firstChild == NotExist && tree[id].secondChild == NotExist)
            {
                tree[id] = currentNode; // Добавить его в дерево
            }
            else
            {
                isCrashed = crashOutput(SAME_NODES_ID);
                return false;
            }

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

        isCrashed = crashOutput(checkOnErrors(size, tree, root));

        if (isCrashed == false)
            return true;
        else
            return false;
    }

}

// Вывести дерево разбора выражений
bool outputTree(int argc, char* argv[], ofstream& fout, vector<Node>& tree, int& current)
{
    bool isCrashed;
    string file2 = argv[2]; // Запоминаем путь к выходному файлу

    // Если расширение выходного файла не равно txt
    if (file2.substr(file2.rfind('.') + 1, string::npos) != "txt") {
        isCrashed = crashOutput(UNKNOWN_FILE_EXTENSION);
        return false;
    }

    fout.open(file2);

    // Если выходной файл для записи не удалось открыть
    if (!fout.is_open()) {
        isCrashed = crashOutput(OUTPUT_FILE_CREATION_FAILED);
        return false;
    }

    if (fout.is_open())
    {
        // Вывести размер дерева
        int tree_size = 0;
        for (int i = 0; i < tree.size(); ++i)
        {
            if (tree[i].value != "")
                tree_size++;
        }
        fout << tree_size;

        // Вывести узлы дерева разбора выражений в порядке обхода в глубину, начиная с корневого
        dfsOutput(fout, tree, current);

        return true;
    }
}

// Вывести сообщение об ошибке
bool crashOutput(ErrorType error)
{
    bool isSuccessOutput = false;

    switch (error)
    {
        case NO_ERROR:
            isSuccessOutput = false;
            break;

        case INPUT_FILE_NOT_EXIST:
            cout << "Неверно указан файл с входными данными. Возможно, файл не существует." << endl;
            isSuccessOutput = true;
            break;

        case UNKNOWN_FILE_EXTENSION:
            cout << "Неверно указано расширение файла. Файл должен иметь расширение .txt" << endl;
            isSuccessOutput = true;
            break;

        case OUTPUT_FILE_CREATION_FAILED:
            cout << "Неверно указан файл для выходных данных. Возможно указанного расположения не существует или нет прав на запись." << endl;
            isSuccessOutput = true;
            break;

        case WRONG_DATA_FORMAT:
            cout << "Программа принимает на вход одно дерево разбора выражений в виде списка смежности. Измените входной файл." << endl;
            isSuccessOutput = true;
            break;

        case NOT_BINARY_TREE:
            cout << "Дерево разбора выражений должно быть бинарным. Измените дерево разбора выражений." << endl;
            isSuccessOutput = true;
            break;

        case SAME_NODES_ID:
            cout << "Узлы дерева разбора выражений не уникальны. Измените дерево разбора выражений на корректное." << endl;
            isSuccessOutput = true;
            break;

        case SAME_PARENT_AND_NODE_ID:
            cout << "Узел дерева разбора выражений не может являться родительским самому себе. Измените дерево разбора выражений на корректное." << endl;
            isSuccessOutput = true;
            break;

        case LACK_OF_OPERANDS:
            cout << "Поддерживаемые операции всегда бинарны. Добавьте операнды, где их недостаёт." << endl;
            isSuccessOutput = true;
            break;

        case NODE_ID_OUT_OF_RANGE:
            cout << "Идентификатором узла должно являться натуральное число в диапазоне [1..30]. Измените идентификаторы узлов дерева разбора выражений на корректные." << endl;
            isSuccessOutput = true;
            break;

        case PARENT_ID_OUT_OF_RANGE:
            cout << "Идентификатором родительского узла для узла в дереве разбора выражений должно являться целое ненулевое число в диапазоне [-1..29]. Измените идентификаторы узлов дерева разбора выражений на корректные." << endl;
            isSuccessOutput = true;
            break;

        case INVALID_NODE_SYMBOL:
            cout << "Дерево разбора выражений задано некорректно. В значении операнда используется недопустимый символ." << endl;
            isSuccessOutput = true;
            break;

        case NOT_RIGHT_LINK:
            cout << "Дерево разбора выражений задано не корректно. Родители и дети совпадают не для всех узлов." << endl;
            isSuccessOutput = true;
            break;

        case UNEXCEPTABLE_PARENT_ID:
            cout << "Родителем узла дерева разбора выражений не может являться его ребёнок. Измените дерево разбора выражений." << endl;
            isSuccessOutput = true;
            break;

        case NO_ROOT:
            cout << "В дереве разбора выражений отсутствует корень. Добавьте его." << endl;
            isSuccessOutput = true;
            break;

        case TREE_SIZE_OUT_OF_RANGE:
            cout << "Число узлов в дереве разбора выражений должно быть натуральным числом в диапазоне [1..30]." << endl;
            isSuccessOutput = true;
            break;

        case INVALID_NUMBER_OF_NODES:
            cout << "Дерево разбора выражений задано некорректно. Указанное и фактическое число узлов в дереве разбора выражений не совпадают." << endl;
            isSuccessOutput = true;
            break;
        default:
            cout << "Произошла неизвестная ошибка. Попробуйте перезапустить программу." << endl;
            isSuccessOutput = true;
            break;
    }

    return isSuccessOutput;
}

// Проверить дерево на ошибки
ErrorType checkOnErrors(int& size, vector<Node>& tree, int& root)
{
    int skippedNodes = 0;
    int treeRoot = 0;
    int treeSize = 0;

    for (int i = 0; i < tree.size(); ++i)
    {
        // Если значение у узла есть
        if (tree[i].value != "")
        {
            // Запомнить атрибуты текущего узла
            int currentID = i;
            int currentParent = tree[i].parent;
            int currentFirstChild = tree[i].firstChild;
            int currentSecondChild = tree[i].secondChild;
            string currentValue = tree[i].value;

            treeSize++; // Увеличить реальный размер дерева

            // Если родитель у узла отсутствует
            if (currentParent == NotExist)
                treeRoot++;

            // Если текущий идентификатор узла вне поддерживаемого диапазона
            if (currentID > MaxSize || currentID < 1)
                return NODE_ID_OUT_OF_RANGE;

            // Если текущий узел - операция и у нее нет двух операндов
            if ((currentValue == "+" || currentValue == "&" || currentValue == "*" || currentValue == "-") && (currentFirstChild == NotExist || currentSecondChild == NotExist))
                return LACK_OF_OPERANDS;

            // Если текущий идентификатор родителя узла вне поддерживаемого диапазона или не отсутствует
            if (currentParent > MaxSize || (currentParent < 1 && currentParent != NotExist))
                return PARENT_ID_OUT_OF_RANGE;

            // Если идентификатор родителя текущего узла совпдаает с идентификатором узла
            if (currentParent == currentID)
                return SAME_PARENT_AND_NODE_ID;

            // Если идентификатор родителя совпадает с идентификатором любого из детей
            if (currentParent!= NotExist && (currentParent == currentFirstChild || currentParent == currentSecondChild))
                return UNEXCEPTABLE_PARENT_ID;

            // Если идентификатор узла не совпадает с идентификатором родительского узла для его детей
            if (currentFirstChild != NotExist && currentSecondChild != NotExist)
            {
                if (currentID != tree[currentFirstChild].parent || currentID != tree[currentSecondChild].parent)
                    return NOT_RIGHT_LINK;
            }

            // Если в значении узла не операция или алфавитно-цифровые символы
            if (!(currentValue == "+" || currentValue == "&" || currentValue == "*" || currentValue == "-"))
            {
                int alphaNumSymbols = 0;
                int plusMinusOpSymbInBegin = 0;

                for (int k = 0; k < currentValue.size(); k++)
                {
                    if (currentValue[0] == '-' || currentValue[0] == '+')
                        plusMinusOpSymbInBegin = 1;

                    if (isalnum(currentValue[k]))
                        alphaNumSymbols++;
                }

                alphaNumSymbols += plusMinusOpSymbInBegin;
                
                if (alphaNumSymbols != currentValue.size())
                    return INVALID_NODE_SYMBOL;
            }

            int numOfUniqueParents = 1; // Считать, что узел-родитель указан таковым для одного из узлов дерева

            // Проходим по дереву и проверяем на уникальность родителей 
            for (int j = 0; j < tree.size(); ++j)
            {

                if (tree[j].value != "" && j != currentID)
                {
                    if ((currentParent != NotExist) && (currentParent == tree[j].parent))
                        numOfUniqueParents++;
                }

                // Если среди узлов есть больше двух с одним родителем
                if (numOfUniqueParents > 2)
                    return NOT_BINARY_TREE;
            }
        }
        else
        {
            skippedNodes++;
        }

    }


    // Если число пустых узлов равно размеру дерева
    if (skippedNodes == tree.size())
        return WRONG_DATA_FORMAT;

    // Если у дерева нет корневого узла
    if (treeRoot == 0)
        return NO_ROOT;

    // Если в данных несколько корневых узлов
    if (treeRoot > 1)
        return WRONG_DATA_FORMAT;

    // Если размер дерева больше максимального
    if (size > MaxSize)
        return TREE_SIZE_OUT_OF_RANGE;

    // Если реальный размер дерева не совпадает с заявленным
    if (treeSize != size)
        return INVALID_NUMBER_OF_NODES;

    return NO_ERROR;
}

// Вывести вершины дерева обходом в глубину
void dfsOutput(ofstream& fout, vector<Node>& tree, int current)
{
    // Вывести значение идентификатора узла, идентификатора его родителя и значение текущего узла
    fout << "\n" << current << " " << tree[current].parent << " " << tree[current].value;

    // Если первый ребёнок текущего узла существует
    if (tree[current].firstChild != NotExist)
        dfsOutput(fout, tree, tree[current].firstChild); // Вывести вершины дерева обходом в глубину, начиная с первого ребёнка текущего узла

    // Если второй ребёнок текущего узла существует
    if (tree[current].secondChild != NotExist)
        dfsOutput(fout, tree, tree[current].secondChild); // Вывести вершины дерева обходом в глубину, начиная со второго ребёнка текущего узла
}

// Скопировать заданную вершину в векторе вершин
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