/*!
* \file Заголовочный файл программы
* Файл содержит в себе структуры и заголовки для функций программы
*/

#pragma once

#include <vector>
using namespace std;

//! Максимальное число узлов в заданном дереве
#define MaxSize 30

//! Отсутствие узла
#define NotExist -1

//! Узел дерева
struct Node
{   
    //! Идентификатор узла-родителя    
    int parent;

    //! Идентификатор узла-первого ребёнка
    int firstChild;

    //! Идентификатор узла-второго ребёнка
    int secondChild; 

    //! Значение узла
    string value; 

    //!> Конструктор узла дерева по умолчанию
    Node()
    {
        this->parent = NotExist; // Считать, что узел-родитель не существует
        this->firstChild = NotExist; // Считать, что узел-первый ребёнок не существует
        this->secondChild = NotExist; // Считать, что узел-второй ребёнок не существует
        this->value = "\0"; // Считать, что у узла отсутствует значение
    }

    //!> Конструктор при явной инициализации
    Node(int parent, int firstChild, int secondChild, string value)
    {
        this->parent = parent;
        this->firstChild = firstChild;
        this->secondChild = secondChild;
        this->value = value;
    }

    //!> Оператор сравнения вершин на равенство
    bool operator == (const Node& other) const
    {
        bool isEqual = false; // Считать, что узлы не равны между собой
       
        // Если все поля узлов совпадают
        if (this->secondChild == other.secondChild && 
            this->firstChild == other.firstChild && 
            this->parent == other.parent && 
            this->value == other.value)
            isEqual = true; // Считать, что узлы равны между собой

        return isEqual;
    }
};

//! Типы ошибок 
enum ErrorType
{
    NO_ERROR, ///< Нет ошибки

    INPUT_FILE_NOT_EXIST, ///< Входной файл не существует
 
    UNKNOWN_FILE_EXTENSION, ///< Входной файл имеет неправильное расширение

    OUTPUT_FILE_CREATION_FAILED, ///< Невозможно создать указанный выходной файл

    WRONG_DATA_FORMAT, ///< Во входном файле формат предоставляемых данных не соответствует требуемому

    NOT_BINARY_TREE, ///< У узлов дерева разбора выражений больше двух детей

    SAME_NODES_ID, ///< Идентификаторы узлов совпадают

    SAME_PARENT_AND_NODE_ID, ///< Идентификатор родительского узла совпадает с идентификатором узла

    LACK_OF_OPERANDS, ///< У операции слишком мало операндов

    NODE_ID_OUT_OF_RANGE, ///< Идентификатор узла дерева разбора выражений вне поддерживаемого диапазона

    PARENT_ID_OUT_OF_RANGE, ///< Идентификатор родительского узла для узла в дереве разбора выражений вне поддерживаемого диапазона

    INVALID_NODE_SYMBOL, ///< Недопустимый символ в значении операнда

    NOT_RIGHT_LINK, ///< Родители и дети у узлов не совпадают

    UNEXCEPTABLE_PARENT_ID, ///< Идентификатор родительского узла является идентификатором узла-ребёнка

    NO_ROOT, ///< Отсутствие корневого узла

    TREE_SIZE_OUT_OF_RANGE, ///< Число узлов дерева разбора выражений вне поддерживаемого диапазона

    INVALID_NUMBER_OF_NODES ///< Указанное число узлов дерева разбора выражений не совпадает с фактическим числом заданных узлов
};

/*! Раскрыть скобки в заданном выражении
    \param[in] currentNode - индекс узла дерева с которого следует раскрывать скобки
    \param[out] tree - дерево разбора выражений
*/
void openBrackets(vector<Node>& tree, int currentNode);

/*! Перестроить часть дерева ниже текущего узла в соответствии с операцией
    \param[in] currentNode - индекс узла дерева с которого следует перестраивать дерево
    \param[in] operation - операция текущего узла
    \param[out] tree - дерево разбора выражений
*/
void replaceTree(vector<Node>& tree, int currentNode, string operation);

/*! Вывести сообщение об ошибке
    \param[in] error - тип ошибки
    \return true при успешном выводе, false - иначе
*/
bool crashOutput(ErrorType error);

/*! Проверить дерево на ошибки
    \param[in] size - размер дерева
    \param[in] root - индекс корня дерева
    \param[in] tree - дерево разбора выражений
    \return обнаруженный тип ошибки
*/
ErrorType checkOnErrors(int& size, vector<Node>& tree, int& root);

/*! Сравнить два дерева между собой
    \param[in] firstTree - первое дерево
    \param[in] rootOfFirstTree - индекс корневого узла первого дерева
    \param[in] secondTree - второе дерево
    \param[in] rootOfSecondTree - индекс корневого узла второго дерева
    \return true - если деревья совпадают, false - если деревья разные
*/
bool isEqualTrees(vector<Node> firstTree, int rootOfFirstTree, vector<Node> secondTree, int rootOfSecondTree);

/*! Заполнить входное дерево до максимального размера
    \param[out] inputTree - дерево разбора выражений
*/
void initializeFullTree(vector<Node>& inputTree);

/*! Ввести заданное дерево разбора выражений
    \param[in] argc - аргумент командной строки
    \param[in] argv[] - аргументы командной строки
    \param[in] fin - входной поток
    \param[out] tree - дерево разбора выражений
    \param[out] root - индекс корня дерева разбора выражений
    \return true - при успешном ввводе, false - иначе
*/
bool inputTree(int argc, char* argv[], ifstream& fin, vector<Node>& tree, int& root);

/*! Вывести дерево разбора выражений
    \param[in] argc - аргумент командной строки
    \param[in] argv[] - аргументы командной строки
    \param[in] tree - дерево разбора выражений
    \param[in] current - индекс вершины, с которой производить вывод дерева
    \param[out] fout - выходной поток
    \return true - при успешном выводе, false - иначе
*/
bool outputTree(int argc, char* argv[], ofstream& fout, vector<Node>& tree, int& current);

/*! Вывести вершины дерева обходом в глубину
    \param[in] tree - дерево разбора выражений
    \param[in] current - идентификатор вершины с которой производить вывод 
    \param[out] fout - выходной поток
*/
void dfsOutput(ofstream& fout, vector<Node>& tree, int current);

/*! Скопировать заданную вершину в векторе вершин
    \param[in] currentNode индекс копируемой вершины
    \param[out] tree вектор вершин
    \return индекс позиции скопированной вершины
*/
int copyVertex(vector<Node>& tree, int currentNode);